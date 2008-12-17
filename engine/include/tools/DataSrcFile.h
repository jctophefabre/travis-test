/**
  \file DataSrcFile.h
  \brief 

  \author Jean-Christophe FABRE <fabrejc@supagro.inra.fr>
*/


#ifndef __DATASRCFILE_H__
#define __DATASRCFILE_H__


#include <wx/string.h>
#include <wx/arrstr.h>
#include <vector>
#include <wx/hashmap.h>



namespace openfluid { namespace tools {

WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, IDDataSourcesMap);

class DataSourcesFile
{
  private:
    bool m_Loaded;
    
    std::vector<int> m_IDs;
  
    IDDataSourcesMap m_Sources;
    
  
  public:
    
    DataSourcesFile();

    virtual ~DataSourcesFile();
    
    bool load(wxString Filename);
    
    std::vector<int> getIDs();
    
    wxString getSource(int ID);    
    
};


} } // namespace



#endif /*__DATASRCFILE_H__*/
