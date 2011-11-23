/*
  This file is part of OpenFLUID software
  Copyright (c) 2007-2010 INRA-Montpellier SupAgro


 == GNU General Public License Usage ==

  OpenFLUID is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  OpenFLUID is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

  In addition, as a special exception, INRA gives You the additional right
  to dynamically link the code of OpenFLUID with code not covered
  under the GNU General Public License ("Non-GPL Code") and to distribute
  linked combinations including the two, subject to the limitations in this
  paragraph. Non-GPL Code permitted under this exception must only link to
  the code of OpenFLUID dynamically through the OpenFLUID libraries
  interfaces, and only for building OpenFLUID plugins. The files of
  Non-GPL Code may be link to the OpenFLUID libraries without causing the
  resulting work to be covered by the GNU General Public License. You must
  obey the GNU General Public License in all respects for all of the
  OpenFLUID code and other code used in conjunction with OpenFLUID
  except the Non-GPL Code covered by this exception. If you modify
  this OpenFLUID, you may extend this exception to your version of the file,
  but you are not obligated to do so. If you do not wish to provide this
  exception without modification, you must delete this exception statement
  from your version and license this OpenFLUID solely under the GPL without
  exception.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
*/


/**
  \file OutBufFunc.cpp
  \brief Implements ...

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
 */


#include <openfluid/base/PlugFunction.hpp>
#include <cmath>
#include <boost/date_time.hpp>

#include <glibmm/thread.h>
#include <glibmm/timer.h>

// =====================================================================
// =====================================================================


DECLARE_PLUGIN_HOOKS

// =====================================================================
// =====================================================================


BEGIN_SIGNATURE_HOOK
  DECLARE_SIGNATURE_ID(("tests.threadedloops"));
  DECLARE_SIGNATURE_NAME(("test function for threaded loops"));
  DECLARE_SIGNATURE_DESCRIPTION((""));

  DECLARE_SIGNATURE_VERSION(("1.0"));
  DECLARE_SIGNATURE_SDKVERSION;
  DECLARE_SIGNATURE_STATUS(openfluid::base::EXPERIMENTAL);

  DECLARE_SIGNATURE_DOMAIN((""));
  DECLARE_SIGNATURE_PROCESS((""));
  DECLARE_SIGNATURE_METHOD((""));
  DECLARE_SIGNATURE_AUTHORNAME((""));
  DECLARE_SIGNATURE_AUTHOREMAIL((""));

  DECLARE_PRODUCED_VAR("tests.data.sequence[double]","TU","sequenced test data","");
  DECLARE_PRODUCED_VAR("tests.data.threaded[double]","TU","threaded test data","");



END_SIGNATURE_HOOK

/**

*/
class ThreadedLoopsFunction : public openfluid::base::PluggableFunction
{
  private:
    Glib::RecMutex m_Mutex;

    openfluid::core::PcsOrd_t m_LastOrd;

  public:


  ThreadedLoopsFunction() : PluggableFunction()
  {


  }


  // =====================================================================
  // =====================================================================


  ~ThreadedLoopsFunction()
  {


  }


  // =====================================================================
  // =====================================================================


  bool initParams(openfluid::core::FuncParamsMap_t /*Params*/)
  {

    return true;
  }

  // =====================================================================
  // =====================================================================


  bool prepareData()
  {

    std::cout << std::endl << "Max threads: " << OPENFLUID_GetFunctionMaxThreads() << std::endl;

    return true;
  }


  // =====================================================================
  // =====================================================================


  bool checkConsistency()
  {


    return true;
  }


  // =====================================================================
  // =====================================================================


  bool initializeRun(const openfluid::base::SimulationInfo* /*SimInfo*/)
  {


    return true;
  }


  // =====================================================================
  // =====================================================================


  void processUnit(openfluid::core::Unit* aUnit)
  {
    if (m_LastOrd > aUnit->getProcessOrder())
      OPENFLUID_RaiseError("tests.threadedloops","processUnit()","wrong process order");
    m_LastOrd = aUnit->getProcessOrder();

    Glib::usleep(100);//*aUnit->getID());
  }


  // =====================================================================
  // =====================================================================


  void produceDataOnTUThreaded(openfluid::core::Unit* aUnit, const openfluid::core::DoubleValue& Value)
  {
    Glib::usleep(100*aUnit->getID());

    Glib::RecMutex::Lock Lock(m_Mutex);
    OPENFLUID_AppendVariable(aUnit,"tests.data.threaded",double(aUnit->getID())+Value/1000.0);
    Lock.release();
  }


  // =====================================================================
  // =====================================================================


  void produceDataOnTUSequenced(openfluid::core::Unit* aUnit, const openfluid::core::DoubleValue& Value)
  {
    Glib::usleep(100*aUnit->getID());
    OPENFLUID_AppendVariable(aUnit,"tests.data.sequence",double(aUnit->getID())+Value/1000.0);
  }


  // =====================================================================
  // =====================================================================


  void processUnitXTimes(openfluid::core::Unit* aUnit, const unsigned int& Times)
  {
    for (unsigned int i=0; i<Times;i++ ) processUnit(aUnit);

  }

  // =====================================================================
  // =====================================================================



  bool runStep(const openfluid::base::SimulationStatus* SimStatus)
  {
    openfluid::core::Unit* TU;

    DECLARE_UNITS_ORDERED_LOOP(1);
    DECLARE_UNITS_ORDERED_LOOP(100);


    DECLARE_GLOBAL_UNITS_ORDERED_LOOP(10);
    DECLARE_GLOBAL_UNITS_ORDERED_LOOP(20);

    std::cout << std::endl;

    boost::posix_time::ptime StartTime, EndTime;
    boost::posix_time::time_duration Duration;


    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    BEGIN_UNITS_ORDERED_LOOP(1,"TU",TU)
      processUnit(TU);
    END_LOOP
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "TU Classic: " << boost::posix_time::to_simple_string(Duration) << std::endl;


    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    APPLY_UNITS_ORDERED_LOOP_THREADED(100,"TU",ThreadedLoopsFunction::processUnit);
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "TU Threaded: " << boost::posix_time::to_simple_string(Duration) << std::endl;


    StartTime = boost::posix_time::microsec_clock::local_time();
    BEGIN_UNITS_ORDERED_LOOP(1,"TU",TU)
      produceDataOnTUSequenced(TU,double(SimStatus->getCurrentStep()));
    END_LOOP
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "TU Production Sequenced: " << boost::posix_time::to_simple_string(Duration) << std::endl;


    StartTime = boost::posix_time::microsec_clock::local_time();
    APPLY_UNITS_ORDERED_LOOP_THREADED(100,"TU",ThreadedLoopsFunction::produceDataOnTUThreaded,double(SimStatus->getCurrentStep()));
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "TU Production Threaded: " << boost::posix_time::to_simple_string(Duration) << std::endl;


    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    BEGIN_UNITS_ORDERED_LOOP(1,"TU",TU)
    processUnitXTimes(TU,3);
    END_LOOP
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "TU Classic 3 times: " << boost::posix_time::to_simple_string(Duration) << std::endl;

    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    APPLY_UNITS_ORDERED_LOOP_THREADED(100,"TU",ThreadedLoopsFunction::processUnitXTimes,3);
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "TU Threaded 3 times: " << boost::posix_time::to_simple_string(Duration) << std::endl;

    // _-_-_-_-_-_-_-_-_-_-_-_-_


    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    BEGIN_GLOBAL_UNITS_ORDERED_LOOP(10,TU)
      processUnit(TU);
    END_LOOP
    EndTime = boost::posix_time::microsec_clock::local_time();
    std::cout << std::endl;
    Duration = EndTime - StartTime;
    std::cout << "Full Classic: " << boost::posix_time::to_simple_string(Duration) << std::endl;

    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    APPLY_GLOBAL_UNITS_ORDERED_LOOP_THREADED(20,ThreadedLoopsFunction::processUnit);
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "Full Threaded: " << boost::posix_time::to_simple_string(Duration) << std::endl;


    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    BEGIN_GLOBAL_UNITS_ORDERED_LOOP(10,TU)
      processUnitXTimes(TU,4);
    END_LOOP
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "Full Classic 4 times: " << boost::posix_time::to_simple_string(Duration) << std::endl;

    StartTime = boost::posix_time::microsec_clock::local_time();
    m_LastOrd = 0;
    APPLY_GLOBAL_UNITS_ORDERED_LOOP_THREADED(20,ThreadedLoopsFunction::processUnitXTimes,4);
    EndTime = boost::posix_time::microsec_clock::local_time();
    Duration = EndTime - StartTime;
    std::cout << "Full Threaded 4 times: " << boost::posix_time::to_simple_string(Duration) << std::endl;


    return true;
  }

  // =====================================================================
  // =====================================================================


  bool finalizeRun(const openfluid::base::SimulationInfo* /*SimInfo*/)
  {


    return true;
  }

};

// =====================================================================
// =====================================================================

DEFINE_FUNCTION_HOOK(ThreadedLoopsFunction)

