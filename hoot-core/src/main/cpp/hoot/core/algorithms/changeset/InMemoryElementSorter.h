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
 * @copyright Copyright (C) 2015, 2016, 2017, 2018 DigitalGlobe (http://www.digitalglobe.com/)
 */
#ifndef IN_MEMORY_ELEMENT_SORTER_H
#define IN_MEMORY_ELEMENT_SORTER_H

// hoot
#include <hoot/core/OsmMap.h>
#include <hoot/core/io/ElementInputStream.h>

// Qt
#include <QFile>
#include <QUrl>

namespace hoot
{

/**
 * An element stream that returns elements in the order of node, way, then relation, sorted by
 * element ID; memory bound as it requires the entire map be passed in to sort the IDs
 */
class InMemoryElementSorter : public ElementInputStream
{

public:

  InMemoryElementSorter(ConstOsmMapPtr map);
  InMemoryElementSorter(const InMemoryElementSorter& sorter);
  virtual ~InMemoryElementSorter() {}

  /**
   * @see ElementInputStream
   */
  virtual boost::shared_ptr<OGRSpatialReference> getProjection() const;

  /**
   * @see ElementInputStream
   */
  virtual void close() {}

  /**
   * @see ElementInputStream
   */
  virtual bool hasMoreElements();

  /**
   * @see ElementInputStream
   */
  virtual ElementPtr readNextElement();

private:

  ConstOsmMapPtr _source;

  std::vector<long> _nodeIds, _wayIds, _relationIds;
  size_t _nodeIndex, _wayIndex, _relationIndex;

};

typedef boost::shared_ptr<InMemoryElementSorter> InMemoryElementSorterPtr;

}

#endif // IN_MEMORY_ELEMENT_SORTER_H