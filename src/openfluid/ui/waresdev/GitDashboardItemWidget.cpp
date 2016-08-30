/*

  This file is part of OpenFLUID software
  Copyright(c) 2007, INRA - Montpellier SupAgro


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
  along with OpenFLUID. If not, see <http://www.gnu.org/licenses/>.


 == Other Usage ==

  Other Usage means a use of OpenFLUID that is inconsistent with the GPL
  license, and requires a written agreement between You and INRA.
  Licensees for Other Usage of OpenFLUID may use this file in accordance
  with the terms contained in the written agreement between You and INRA.
  
*/


/**
  @file GitDashboardItemWidget.cpp

  @author Jean-Christophe FABRE <jean-christophe.fabre@supagro.inra.fr>
*/


#include <openfluid/ui/waresdev/GitDashboardItemWidget.hpp>
#include <openfluid/base/Environment.hpp>

#include "ui_GitDashboardItemWidget.h"


static const QString COLOR_WARN = "#ffa90b"; //#ffb327
static const QString COLOR_OK = "#0fb727";
static const QString COLOR_LIGHT = "#555555";


namespace openfluid { namespace ui { namespace waresdev {


GitDashboardItemWidget::GitDashboardItemWidget(const WorkspaceGitDashboardWorker::WareStatusInfo& Infos,
                                               QWidget* Parent) :
    QFrame(Parent), ui(new Ui::GitDashboardItemWidget),
    m_ExpectedBranchName("openfluid-"+QString::fromStdString(openfluid::base::Environment::getVersionMajorMinor()))
{
  ui->setupUi(this);


  ui->WareIDLabel->setText(Infos.ID);


  if (Infos.BranchName != m_ExpectedBranchName)
    ui->BranchLabel->setText("<font style='color: "+COLOR_WARN+";'>"+Infos.BranchName+"</font>");
  else
    ui->BranchLabel->setText("<font style='color: "+COLOR_OK+";'>"+Infos.BranchName+"</font>");


  ui->StatusLabel->setText(getStatusString(Infos));
}


// =====================================================================
// =====================================================================


GitDashboardItemWidget::~GitDashboardItemWidget()
{
  delete ui;
}


// =====================================================================
// =====================================================================


void GitDashboardItemWidget::updateStatusString(QString& CurrentStr, const QString& State, int Counter)
{
  if (Counter)
  {
    if (!CurrentStr.isEmpty())
      CurrentStr += ", ";

    CurrentStr += QString("%1 "+State).arg(Counter);
  }
}


// =====================================================================
// =====================================================================


QString GitDashboardItemWidget::getStatusString(const WorkspaceGitDashboardWorker::WareStatusInfo& Infos)
{
  QString StatusStr;

  updateStatusString(StatusStr,
                     tr("dirty"),Infos.DirtyCounter);
  updateStatusString(StatusStr,
                     tr("untracked"),Infos.IndexCounters.at(openfluid::utils::GitHelper::FileStatus::UNTRACKED));
  updateStatusString(StatusStr,
                     tr("modified"),Infos.IndexCounters.at(openfluid::utils::GitHelper::FileStatus::MODIFIED));
  updateStatusString(StatusStr,
                     tr("added"),Infos.IndexCounters.at(openfluid::utils::GitHelper::FileStatus::ADDED));
  updateStatusString(StatusStr,
                     tr("deleted"),Infos.IndexCounters.at(openfluid::utils::GitHelper::FileStatus::DELETED));
  updateStatusString(StatusStr,
                     tr("conflict"),Infos.IndexCounters.at(openfluid::utils::GitHelper::FileStatus::CONFLICT));

  if (StatusStr.isEmpty())
    StatusStr = "<font style='color: "+COLOR_OK+";'>"+tr("clean")+"</font>";
  else
    StatusStr = "<font style='color: "+COLOR_WARN+";'>"+StatusStr+"</font>";

  return StatusStr;
}


} } } // namespaces

