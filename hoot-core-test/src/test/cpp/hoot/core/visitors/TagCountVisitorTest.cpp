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
 * @copyright Copyright (C) 2014, 2015, 2017, 2018 DigitalGlobe (http://www.digitalglobe.com/)
 */

// CPP Unit
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestFixture.h>

// hoot
#include <hoot/core/elements/OsmMap.h>
#include <hoot/core/TestUtils.h>
#include <hoot/core/io/OsmXmlReader.h>
#include <hoot/core/visitors/TagCountVisitor.h>

namespace hoot
{

class TagCountVisitorTest : public HootTestFixture
{
  CPPUNIT_TEST_SUITE(TagCountVisitorTest);
  CPPUNIT_TEST(totalTagCountTest);
  CPPUNIT_TEST(informationTagCountTest);
  CPPUNIT_TEST_SUITE_END();

public:

  TagCountVisitorTest()
  {
    setResetType(ResetBasic);
  }

  void totalTagCountTest()
  {
    ConstOsmMapPtr constMap = _loadMap();

    TagCountVisitor tagCountVisitor;
    constMap->visitRo(tagCountVisitor);

    CPPUNIT_ASSERT_EQUAL((long)13, (long)tagCountVisitor.getStat());
  }

  void informationTagCountTest()
  {
    ConstOsmMapPtr constMap = _loadMap();

    TagCountVisitor tagCountVisitor;
    constMap->visitRo(tagCountVisitor);

    CPPUNIT_ASSERT_EQUAL((long)7, tagCountVisitor.getInformationCount());
  }

private:

  ConstOsmMapPtr _loadMap()
  {
    OsmXmlReader reader;
    OsmMapPtr map(new OsmMap());
    reader.setDefaultStatus(Status::Unknown1);
    reader.read("test-files/visitors/TagCountVisitorTest.osm", map);
    ConstOsmMapPtr constMap = map;
    return constMap;
  }

};

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(TagCountVisitorTest, "quick");

}


