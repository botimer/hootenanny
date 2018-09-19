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
 * @copyright Copyright (C) 2016, 2017, 2018 DigitalGlobe (http://www.digitalglobe.com/)
 */
#ifndef FINDNODESVISITOR_H
#define FINDNODESVISITOR_H

#include <hoot/core/visitors/ElementConstOsmMapVisitor.h>

// For convenience functions
#include <hoot/core/criterion/TagCriterion.h>

namespace hoot
{

class ElementCriterion;

// Used to get a vector of IDs for the nodes that satisfy
// the specified criterion
class FindNodesVisitor : public ElementConstOsmMapVisitor
{
public:

  static std::string className() { return "hoot::FindNodesVisitor"; }

  FindNodesVisitor(ElementCriterion* pCrit);

  void setOsmMap(const OsmMap* map) { _map = map; }

  void visit(const boost::shared_ptr<const Element>& e);

  // Get matching IDs
  std::vector<long> getIds() { return _nodeIds; }

  static std::vector<long> findNodes(const ConstOsmMapPtr& map,
                                    ElementCriterion* pCrit);

  static std::vector<long> findNodes(const ConstOsmMapPtr& map,
                                     ElementCriterion* pCrit,
                                     const geos::geom::Coordinate& refCoord,
                                     Meters maxDistance);

  // Convenience method for finding nodes that contain the given tag
  static std::vector<long> findNodesByTag(const ConstOsmMapPtr& map,
                                          const QString& key,
                                          const QString& value);

  virtual QString getDescription() const { return "Returns the node IDs visited"; }

private:

  const OsmMap* _map;
  std::vector<long> _nodeIds;
  ElementCriterion * _pCrit;
};

}

#endif // FINDNODESVISITOR_H
