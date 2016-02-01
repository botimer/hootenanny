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
 * @copyright Copyright (C) 2014 DigitalGlobe (http://www.digitalglobe.com/)
 */

//
// NAVTEQ Conversion
//

hoot.require('navteq')
hoot.require('navteq_rules')
hoot.require('config')
hoot.require('translate')


function initialize()
{
        if (typeof navteq === 'undefined')
        {           
            logError('Please install the NAVTEQ Translation scripts.');
        }                           
}


// IMPORT
// translateAttributes - takes 'attrs' and returns OSM 'tags'
// function translateAttributes(attrs, layerName)
function translateToOsm(attrs, layerName, geometryType)
{
    if (typeof navteq !== 'undefined')
    {       
        return navteq.toOsm(attrs, layerName, geometryType);
    }                       
    else
    {           
        return attrs; 
    }

} // End of Translate Attributes


