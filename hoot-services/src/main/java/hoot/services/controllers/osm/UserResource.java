/*
 * This file is part of Hootenanny.
 *
 * Hootenanny is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * The following copyright notices are generated automatically. If you
 * have a new notice to add, please use the format:
 * " * @copyright Copyright ..."
 * This will properly maintain the copyright information. DigitalGlobe
 * copyrights will be updated automatically.
 *
 * @copyright Copyright (C) 2015, 2016 DigitalGlobe (http://www.digitalglobe.com/)
 */
package hoot.services.controllers.osm;

import java.io.IOException;
import java.sql.Connection;
import java.util.List;

import javax.ws.rs.Consumes;
import javax.ws.rs.GET;
import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.QueryParam;
import javax.ws.rs.WebApplicationException;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.Response.Status;
import javax.xml.transform.dom.DOMSource;

import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.w3c.dom.Document;

import com.mysema.query.sql.SQLQuery;

import hoot.services.db.DbUtils;
import hoot.services.db2.QUsers;
import hoot.services.db2.Users;
import hoot.services.models.osm.ModelDaoUtils;
import hoot.services.models.osm.User;
import hoot.services.models.user.UserSaveResponse;
import hoot.services.models.user.UsersGetResponse;
import hoot.services.readers.users.UsersRetriever;
import hoot.services.utils.XmlDocumentBuilder;
import hoot.services.writers.osm.UserResponseWriter;
import hoot.services.writers.user.UserSaver;


/**
 * Service endpoint for OSM user information
 */
@Path("/user/{userId}")
public class UserResource {
    private static final Logger logger = LoggerFactory.getLogger(UserResource.class);

    public UserResource() {

    }

    /**
     * Service method endpoint for retrieving OSM user information
     * 
     * This is currently implemented as a dummy method to appease iD. It always
     * retrieves information for the first user record in the services database.
     * It cannot properly be implemented until user authentication is first
     * implemented.
     * 
     * GET hoot-services/osm/api/0.6/user/details
     *
     * @param userId
     *            ID of the user to retrieve information for
     * @return Response with the requested user's information
     */
    @GET
    @Consumes(MediaType.TEXT_PLAIN)
    @Produces(MediaType.TEXT_XML)
    public Response get(@PathParam("userId") String userId) {
        logger.debug("Retrieving user with ID: {} ...", userId.trim());

        Connection conn = DbUtils.createConnection();
        Document responseDoc = null;
        try {
            logger.debug("Initializing database connection...");

            long userIdNum;
            try {
                QUsers users = QUsers.users;
                // input mapId may be a map ID or a map name
                userIdNum = ModelDaoUtils.getRecordIdForInputString(userId, conn, users, users.id, users.displayName);
            }
            catch (Exception e) {
                if (e.getMessage().startsWith("Multiple records exist") ||
                        e.getMessage().startsWith("No record exists")) {
                    String message = e.getMessage().replaceAll("records", "users").replaceAll("record", "user");
                    throw new WebApplicationException(e, Response.status(Status.NOT_FOUND).entity(message).build());
                }
                else {
                    String message = "Error requesting user with ID: " + userId + " (" + e.getMessage() + ")";
                    throw new WebApplicationException(e, Response.status(Status.BAD_REQUEST).entity(message).build());
                }
            }

            QUsers usersTbl = QUsers.users;

            SQLQuery query = new SQLQuery(conn, DbUtils.getConfiguration());

            // there is only ever one test user
            Users user = query.from(usersTbl).where(usersTbl.id.eq(userIdNum)).singleResult(usersTbl);

            if (user == null) {
                String message = "No user exists with ID: " + userId + ".  Please request a valid user.";
                throw new WebApplicationException(Response.status(Status.NOT_FOUND).entity(message).build());
            }

            responseDoc = (new UserResponseWriter()).writeResponse(new User(user));
        }
        finally {
            DbUtils.closeConnection(conn);
        }

        try {
            logger.debug("Returning response: {} ...", StringUtils.abbreviate(XmlDocumentBuilder.toString(responseDoc), 100));
        }
        catch (IOException ignored) {
        }

        return Response.ok(new DOMSource(responseDoc), MediaType.APPLICATION_XML)
                .header("Content-type", MediaType.APPLICATION_XML).build();
    }

    /**
     * Service method endpoint for retrieving OSM user information. This rest
     * end point retrieves user based on user email. If it does not exist then
     * it creates first.
     * 
     * @param userEmail
     *            User email to save/get
     * @return Response with the requested user's information
     */
    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public UserSaveResponse getSaveUser(@QueryParam("userEmail") String userEmail) {
        UserSaveResponse response;
        try {
            try (Connection conn = DbUtils.createConnection()) {
                UserSaver saver = new UserSaver(conn);
                Users user = saver.getOrSaveByEmail(userEmail);
                if (user == null) {
                    throw new Exception("SQL Insert failed.");
                }

                response = new UserSaveResponse(user);
            }
        }
        catch (Exception ex) {
            String message = "Error saving user: " + " (" + ex.getMessage() + ")";
            throw new WebApplicationException(ex, Response.status(Status.BAD_REQUEST).entity(message).build());
        }

        return response;
    }

    /**
     * This rest end point retrieves all users based on user email.
     * 
     * GET hoot-services/osm/user/1/all
     *
     * @return JSONArray Object containing users detail
     */
    @GET
    @Path("/all")
    @Produces(MediaType.APPLICATION_JSON)
    public UsersGetResponse getAllUsers() {
        try {
            try (Connection conn = DbUtils.createConnection()) {
                UsersRetriever retriever = new UsersRetriever(conn);
                List<Users> res = retriever.retrieveAll();

                UsersGetResponse response = new UsersGetResponse(res);
                return response;
            }
        }
        catch (Exception ex) {
            String message = "Error getting all users: " + " (" + ex.getMessage() + ")";
            throw new WebApplicationException(ex, Response.status(Status.BAD_REQUEST).entity(message).build());
        }
    }
}
