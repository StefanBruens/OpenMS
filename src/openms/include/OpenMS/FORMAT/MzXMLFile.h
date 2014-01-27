// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2013.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Andreas Bertsch $
// $Authors: Marc Sturm $
// --------------------------------------------------------------------------

#ifndef OPENMS_FORMAT_MZXMLFILE_H
#define OPENMS_FORMAT_MZXMLFILE_H

#include <OpenMS/FORMAT/XMLFile.h>
#include <OpenMS/CONCEPT/ProgressLogger.h>
#include <OpenMS/FORMAT/OPTIONS/PeakFileOptions.h>
#include <OpenMS/FORMAT/HANDLERS/MzXMLHandler.h>

namespace OpenMS
{
  class String;

  /**
      @brief File adapter for MzXML 2.1 files

      @ingroup FileIO
  */
  class OPENMS_DLLAPI MzXMLFile :
    public Internal::XMLFile,
    public ProgressLogger
  {
public:
    ///Default constructor
    MzXMLFile();
    ///Destructor
    ~MzXMLFile();

    /// Mutable access to the options for loading/storing
    PeakFileOptions & getOptions();

    /// Non-mutable access to the options for loading/storing
    const PeakFileOptions & getOptions() const;

    /// set options for loading/storing
    void setOptions(const PeakFileOptions &);

    /**
        @brief Loads a map from a MzXML file.

        @p map has to be a MSExperiment or have the same interface.

        @exception Exception::FileNotFound is thrown if the file could not be opened
        @exception Exception::ParseError is thrown if an error occurs during parsing
    */
    template <typename MapType>
    void load(const String & filename, MapType & map)
    {
      map.reset();

      //set DocumentIdentifier
      map.setLoadedFileType(filename);
      map.setLoadedFilePath(filename);

      Internal::MzXMLHandler<MapType> handler(map, filename, schema_version_, *this);
      handler.setOptions(options_);
      parse_(filename, &handler);
    }

    /**
        @brief Stores a map in a MzXML file.

        @p map has to be a MSExperiment or have the same interface.

        @exception Exception::UnableToCreateFile is thrown if the file could not be created
    */
    template <typename MapType>
    void store(const String & filename, const MapType & map) const
    {
      Internal::MzXMLHandler<MapType> handler(map, filename, schema_version_, *this);
      save_(filename, &handler);
    }

private:
    PeakFileOptions options_;
  };
} // namespace OpenMS

#endif // OPENMS_FOMAT_MZXMLFILE_H