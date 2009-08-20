/**
  \file PluginManager.h
  \brief header of the plugins management class

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/


#ifndef __PLUGINMANAGER_H__
#define __PLUGINMANAGER_H__

#include "openfluid-base.h"
#include "openfluid-core.h"
#include "RuntimeEnv.h"


struct PluginContainer
{

  std::string Filename;
  bool SDKCompatible;
  openfluid::base::FunctionSignature* Signature;
  openfluid::base::PluggableFunction* Function;

  PluginContainer()
  {
    Filename = "";
    Signature = NULL;
    Function = NULL;
    SDKCompatible = false;
  }

};


typedef std::vector<openfluid::base::FunctionSignature*> ArrayOfPluginsSignatures;
typedef std::vector<PluginContainer*> ArrayOfPluginsContainers;

/**
  Management class for plugins
*/
class PluginManager
{
  private:

    RuntimeEnvironment* mp_RunEnv;
    openfluid::base::ExecutionMessages* mp_ExecMsgs;

/*    openfluid::base::PluggableFunction *getPluggableFunction(std::string PluginFilename);*/
    PluginContainer *buildPluginContainer(std::string PluginFilename);



  public:
    /**
      Constructor
    */
    PluginManager(openfluid::base::ExecutionMessages* ExecMsgs, RuntimeEnvironment* RunEnv);

    /**
      Destructor
    */
    ~PluginManager();

    /**
      Lists available simulation functions
    */
//    ArrayOfPluginsSignatures getAvailableFunctionsList();

    ArrayOfPluginsContainers getAvailableFunctions(const std::string Pattern = "");


    /**
      Returns function and function types
    */
    PluginContainer *getPlugin(std::string PluginName,
                               openfluid::core::CoreRepository* CoreData);

/*
    openfluid::base::Function *getFunctionFromPlugin(std::string PluginName,
                                          openfluid::base::ModuleTypeList ReqModType,
                                          openfluid::base::FunctionTypeList ReqFuncType);
*/

};





#endif


