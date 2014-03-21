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
// $Maintainer: Lars Nilse $
// $Authors: Lars Nilse $
// --------------------------------------------------------------------------

#ifndef OPENMS_FILTERING_DATAREDUCTION_SPLINESPECTRUM_H
#define OPENMS_FILTERING_DATAREDUCTION_SPLINESPECTRUM_H

#include <OpenMS/KERNEL/StandardTypes.h>
#include <OpenMS/DATASTRUCTURES/DRange.h>
#include <OpenMS/MATH/MISC/Spline2d.h>
#include <OpenMS/FILTERING/DATAREDUCTION/SplinePackage.h>

#include <vector>
#include <algorithm>
#include <iostream>

namespace OpenMS
{
  /**
   * @brief data structure for spline interpolation of MS1 spectra
   * 
   * The data structure consists of a set of splines, each interpolating the MS1 spectrum in a certain m/z range.
   * Between these splines no raw data points exist and the spectrum intensity is identical to zero.
   *
   * @see SplinePackage
   * @see MSSpectrum<Peak1D>
   */
  class OPENMS_DLLAPI SplineSpectrum
  {
    /**
     * @brief set of spline packages each interpolating in a certain m/z range
     */
    std::vector<SplinePackage> packages_;
 
	public:
    /**
     * @brief constructor taking two vectors
     */
    SplineSpectrum(std::vector<double> mz, std::vector<double> intensity);
    
    /**
     * @brief constructor taking an MSSpectrum
     */
    SplineSpectrum(MSSpectrum<Peak1D> rawSpectrum);

    /**
     * @brief returns the spline interpolated intensity @ m/z
     * (NB for fast access use SplineSpectrum::Navigator)
     */
    double eval(double mz);

    /**
     * @brief returns the next sensible m/z position
     *  for scanning through a spectrum
     * (NB for fast access use SplineSpectrum::Navigator)
     */
    double getNextMz(double mz);
    
    /**
     * @brief section common for both constructors
     */
    void init(std::vector<double> mz, std::vector<double> intensity);
    
    /**
     * @brief iterator class for access of spline packages
     */
   class Navigator
    {
        /**
         * @brief list of spline packages to be accessed
         */
        const std::vector<SplinePackage> * packages_;
        
        /**
         * @brief index of spline package last accessed
         */
        unsigned lastPackage_;
        
        public:
        /**
         * @brief constructor of iterator
         */
        Navigator(const std::vector<SplinePackage> * packages);
        
        /**
         * @brief returns spline interpolated intensity at m/z
         * (fast access since we can start search from lastPackage)
         */
        double eval(double mz);
        
        /**
         * @brief returns the next sensible m/z position
         *  for scanning through a spectrum
         * (fast access since we can start search from lastPackage)
         */
        double getNextMz(double mz);
    };
    
    /**
     * @brief returns an iterarator for access of spline packages
     */
    SplineSpectrum::Navigator getNavigator();
    
 };
  
}

#endif /* SPLINESPECTRUM_H_ */
