from libcpp cimport bool
from libcpp.map cimport map as libcpp_map
from libcpp.pair cimport pair as libcpp_pair
from libcpp.vector cimport vector as libcpp_vector
from Types cimport *
from String cimport *
from PeptideIdentification cimport *
from DateTime cimport *

cdef extern from "<OpenMS/FORMAT/SequestOutfile.h>" namespace "OpenMS":
    
    cdef cppclass SequestOutfile "OpenMS::SequestOutfile":
        SequestOutfile() nogil except +
        SequestOutfile(SequestOutfile) nogil except +
        bool operator==(SequestOutfile &sequest_outfile) nogil except +
        void load(String &result_filename, libcpp_vector[ PeptideIdentification ] &peptide_identifications, ProteinIdentification &protein_identification, DoubleReal p_value_threshold, libcpp_vector[ double ] &pvalues, String &database, bool ignore_proteins_per_peptide) nogil except +
        bool getColumns(String &line, libcpp_vector[ String ] &substrings, Size number_of_columns, Size reference_column) nogil except +
        # void getSequences(String &database_filename, libcpp_map[ String, Size ] &ac_position_map, libcpp_vector[ String ] &sequences, libcpp_vector[ libcpp_pair[ String, Size ] ] &found, libcpp_map[ String, Size ] &not_found) nogil except +
        void getACAndACType(String line, String &accession, String &accession_type) nogil except +
        void readOutHeader(String &result_filename, DateTime &datetime, DoubleReal &precursor_mz_value, Int &charge, Size &precursor_mass_type, Size &ion_mass_type, Size &displayed_peptides, String &sequest, String &sequest_version, String &database_type, Int &number_column, Int &rank_sp_column, Int &id_column, Int &mh_column, Int &delta_cn_column, Int &xcorr_column, Int &sp_column, Int &sf_column, Int &ions_column, Int &reference_column, Int &peptide_column, Int &score_column, Size &number_of_columns) nogil except +
