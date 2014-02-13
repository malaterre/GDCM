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
#ifndef GDCMNORMALIZEDNETWORKFUNCTIONS_H
#define GDCMNORMALIZEDNETWORKFUNCTIONS_H

#include "gdcmDirectory.h"
#include "gdcmBaseQuery.h" // EQueryLevel / EQueryType

#include <vector>
#include <string>

namespace gdcm
{
/**
 * \brief Normalized Network Functions
 * These functions provide a generic API to the DICOM functions implemented in
 * GDCM.
 * Advanced users can use this code as a template for building their own
 * versions of these functions (for instance, to provide progress bars or some
 * other way of handling returned query information), but for most users, these
 * functions should be sufficient to interface with a PACS to a local machine.
 * Note that these functions are not contained within a static class or some
 * other class-style interface, because multiple connections can be
 * instantiated in the same program.  The DICOM standard is much more function
 * oriented rather than class oriented in this instance, so the design of this
 * API reflects that functional approach.
 * These functions implements the following SCU operations:
 * \li N-EVENT-REPORT
 * \li N-GET
 * \li N-SET
 * \li N-ACTION
 * \li N-CREATE
 * \li N-DELETE
 */
class GDCM_EXPORT NormalizedNetworkFunctions 
{
public:
	static BaseQuery* ConstructQuery(	const std::string & sopInstanceUID, 
										const DataSet& queryds, ENQueryType queryType = eMMPS );
	static bool NEventReport( const char *remote, uint16_t portno,
							  const BaseQuery* query, std::vector<DataSet> &retDataSets,
							  const char *aetitle, const char *call );
  static bool NGet( const char *remote, uint16_t portno,
										  const BaseQuery* query, std::vector<DataSet> &retDataSets,
										  const char *aetitle, const char *call );
  static bool NSet( const char *remote, uint16_t portno,
										  const BaseQuery* query, std::vector<DataSet> &retDataSets,
										  const char *aetitle, const char *call );
  static bool NAction( const char *remote, uint16_t portno,
										  const BaseQuery* query, std::vector<DataSet> &retDataSets,
										  const char *aetitle, const char *call );
  static bool NCreate( const char *remote, uint16_t portno,
										  BaseQuery* query, std::vector<DataSet> &retDataSets,
										  const char *aetitle, const char *call );
  static bool NDelete( const char *remote, uint16_t portno,
										  const BaseQuery* query, std::vector<DataSet> &retDataSets,
										  const char *aetitle, const char *call );
};

} // end namespace gdcm

#endif // GDCMCOMPOSITENETWORKFUNCTIONS_H
