/**
  \file
  \brief implements ...

  \author Jean-Christophe FABRE <fabrejc@ensam.inra.fr>
*/



#include "Module.h"

#include <wx/listimpl.cpp>
WX_DEFINE_LIST(FunctionsList);


// =====================================================================
// =====================================================================

#define PARSE_FUNCTION_LIST(calledmethod,statevar) \
    FunctionsList::Node *Node = m_Functions.GetFirst(); \
    while (Node && statevar) \
    { \
      mhydasdk::base::Function* CurrentFunction = (mhydasdk::base::Function*)Node->GetData(); \
      if (CurrentFunction != NULL) statevar = statevar && CurrentFunction->calledmethod; \
      Node = Node->GetNext(); \
    }

// =====================================================================
// =====================================================================



Module::Module(mhydasdk::core::CoreRepository* CoreData, FunctionsList Functions)
      : mhydasdk::base::ComputationBlock(CoreData)
{
  m_Functions = Functions;

}

// =====================================================================
// =====================================================================



Module::~Module()
{

}



// =====================================================================
// =====================================================================

bool Module::prepareData()
{
  bool IsOK = true;

  if (m_Functions.GetCount() == 0) IsOK = false;
  else
  {
    PARSE_FUNCTION_LIST(prepareData(),IsOK);
  }

  return IsOK;
}


// =====================================================================
// =====================================================================


bool Module::checkConsistency()
{
  bool IsOK = true;

  if (m_Functions.GetCount() == 0) IsOK = false;
  else
  {
    PARSE_FUNCTION_LIST(checkConsistency(),IsOK);
  }

  return IsOK;
}


// =====================================================================
// =====================================================================


bool Module::initializeRun()
{
  bool IsOK = true;

  PARSE_FUNCTION_LIST(initializeRun(),IsOK);

  return IsOK;
}


// =====================================================================
// =====================================================================


bool Module::runStep(mhydasdk::base::SimulationStatus* SimStatus)
{
  bool IsOK = true;

  PARSE_FUNCTION_LIST(runStep(SimStatus),IsOK);

  return IsOK;

}


// =====================================================================
// =====================================================================


bool Module::finalizeRun()
{
  bool IsOK = true;

  PARSE_FUNCTION_LIST(finalizeRun(),IsOK);

  return IsOK;

}







