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
 * @copyright Copyright (C) 2018 DigitalGlobe (http://www.digitalglobe.com/)
 */

#ifndef ADDRESS_COUNT_VISITOR_H
#define ADDRESS_COUNT_VISITOR_H

// hoot
#include <hoot/core/elements/ConstElementVisitor.h>
#include <hoot/core/visitors/SingleStatistic.h>
#include <hoot/core/util/Configurable.h>
#include <hoot/core/conflate/address/AddressParser.h>

namespace hoot
{

/**
 * Counts the number of valid element addresses
 */
class AddressCountVisitor : public ConstElementVisitor, public SingleStatistic, public Configurable
{
public:

  static std::string className() { return "hoot::AddressCountVisitor"; }

  AddressCountVisitor();

  virtual void setConfiguration(const Settings& conf);

  double getStat() const { return _totalCount; }

  virtual void visit(const ConstElementPtr& e);

  virtual QString getDescription() const
  { return "Counts the total number of valid element addresses"; }

private:

  int _totalCount;
  AddressParser _addressParser;
};

}

#endif // ADDRESS_COUNT_VISITOR_H