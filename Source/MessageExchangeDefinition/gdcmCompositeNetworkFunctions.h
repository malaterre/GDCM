/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#ifndef GDCMCOMPOSITENETWORKFUNCTIONS_H
#define GDCMCOMPOSITENETWORKFUNCTIONS_H

#include <vector>
#include <string>
#include "gdcmTypes.h"

namespace gdcm{
  class DataSet;
  class Tag;
  namespace network{
    class BaseRootQuery;
  }
  /// These functions provide a generic API to the DICOM functions implemented in GDCM.
  /// Advanced users can use this code as a template for building their own versions of
  /// these functions (for instance, to provide progress bars or some other way of handling
  /// returned query information), but for most users, these functions should be
  /// sufficient to interface with a PACS to a local machine.
  /// Note that these functions are not contained within a static class or some other
  /// class-style interface, because multiple connections can be instantiated in the same program.
  /// The DICOM standard is much more function oriented rather than class oriented in this
  /// instance, so the design of this API reflects that functional approach

  /// The most basic network function.  Use this function to ensure that the remote server is
  /// responding on the given IP and port number as expected.
  /// Returns true if it worked.
  class GDCM_EXPORT CompositeNetworkFunctions 
    {
    public:
    bool CEcho( const char *remote, int portno, const std::string& aetitle,
                const std::string& call );

    ///This function will take a list of strings and tags and fill in a query that can be used
    ///for either CFind or CMove (depending on the input boolean inMove).
    ///Note that the caller is responsible for deleting the constructed query.
    ///This function is used to build both a move and a find query 
    ///(true for inMove if it's move, false if it's find)
    gdcm::network::BaseRootQuery* ConstructQuery(bool inMove, bool findstudy, bool findpatient,
                                                 const std::vector< std::pair<gdcm::Tag, std::string> >& keys);


    ///This function will use the provided query to get files from a remote server.
    ///NOTE that this functionality is essentially equivalent to C-Get in the DICOM standard;
    ///however, C-Get has been deprecated, so this function allows for the user to ask a remote server
    ///for files matching a query and return them to the local machine.
    ///Files will be written to the given output directory.
    ///If the operation succeeds, the function returns true.
    ///This function is a prime candidate for being overwritten by expert users; if the datasets
    ///should remain in memory, for instance, that behavior can be changed by creating a user-level version
    ///of this function.
    bool CMove( const char *remote, int portno, std::string const &aetitle,
                const std::string& call, gdcm::network::BaseRootQuery* query,
                int portscp, const std::string& outputdir);


    ///This function wil use the provided query to determine what files a remote server contains
    ///that match the query strings.  The return is a vector of datasets that contain tags as reported
    ///by the server.  If the dataset is empty, then it is possible that an error condition was encountered;
    ///in which case, the user should monitor the error and warning streams.
    std::vector<gdcm::DataSet> CFind( const char *remote, int portno , std::string const &aetitle,
                                      std::string const &call , gdcm::network::BaseRootQuery* query );

    ///This function will place the provided files into the remote server.
    ///The function returns true if it worked.
    bool CStore( const char *remote, int portno,
                 std::string const &aetitle, std::string const &call,
                 std::vector<std::string> const & filenames, bool inRecursive );
    };
}

#endif //GDCMCOMPOSITENETWORKFUNCTIONS_H