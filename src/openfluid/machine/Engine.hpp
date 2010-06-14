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
  @file

  @author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/


#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__


#include <openfluid/dllexport.hpp>
#include <openfluid/core.hpp>
#include <openfluid/base.hpp>
#include <openfluid/io/IOMan.hpp>
#include <openfluid/machine/PluginManager.hpp>
#include <openfluid/base/RuntimeEnv.hpp>
#include <openfluid/machine/ModelInstance.hpp>
#include <openfluid/machine/MachineListener.hpp>
#include <openfluid/io/IOListener.hpp>

namespace openfluid { namespace machine {


// =====================================================================
// =====================================================================


/**
  Computation engine class
*/
class DLLEXPORT Engine
{
  private:

     openfluid::core::CoreRepository* mp_CoreData;

     openfluid::base::RuntimeEnvironment* mp_RunEnv;

     openfluid::base::ExecutionMessages* mp_ExecMsgs;

     openfluid::base::SimulationStatus* mp_SimStatus;

     /**
       Plugin manager
     */
     PluginManager* mp_PlugMan;


     /**
       IOManager
     */
     openfluid::io::IOManager* mp_IOMan;


     openfluid::base::ModelDescriptor m_ModelDesc;

     openfluid::base::RunDescriptor m_RunDesc;

     openfluid::base::DomainDescriptor m_DomainDesc;

     MachineListener* mp_Listener;

     const ModelInstance* mp_ModelInstance;


     void checkSimulationVarsProduction(int ExpectedVarsCount);

     void checkModelConsistency();

     void checkDataConsistency();

     void checkExtraFilesConsistency();

     void checkExistingVariable(openfluid::core::VariableName_t VarName,
                                openfluid::core::UnitClass_t ClassName,
                                std::string FunctionName);

     void createVariable(openfluid::core::VariableName_t VarName,
                         openfluid::core::UnitClass_t ClassName,
                         bool UpdateMode,
                         std::string FunctionName);

     void checkExistingInputData(openfluid::core::InputDataName_t DataName,
                                 openfluid::core::UnitClass_t ClassName,
                                 std::string FunctionName);

  public:
    /**
      Constructor
    */
    Engine(openfluid::machine::MachineListener* MachineListener,
           openfluid::io::IOListener* IOListener);

    /**
      Destructor
    */
    ~Engine();

    bool buildModel();

    bool buildSpatialDomain();

    bool loadData();

    bool processRunConfiguration();

    bool initParams();

    bool prepareDataAndCheckConsistency();

    bool run();

    bool saveReports();

    void closeOutputs();

    openfluid::base::SimulationInfo *getSimulationInfo() { return (openfluid::base::SimulationInfo*)mp_SimStatus; };

};


} } //namespaces


#endif






