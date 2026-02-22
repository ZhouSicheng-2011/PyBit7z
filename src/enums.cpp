#include <API.hpp>
#include <pybind11/native_enum.h>

void init_enums(py::module& mod){
    /*
    Init the enums of bit7z
    */

    //Bind BitCompressionLevel
    py::native_enum<bit7z::BitCompressionLevel>(mod, "BitCompressionLevel")
        .value("None", bit7z::BitCompressionLevel::None)
        .value("Fastest", bit7z::BitCompressionLevel::Fastest)
        .value("Fast", bit7z::BitCompressionLevel::Fast)
        .value("Normal", bit7z::BitCompressionLevel::Normal)
        .value("Max", bit7z::BitCompressionLevel::Max)
        .value("Ultra", bit7z::BitCompressionLevel::Ultra)
        .export_values()
        .finalize();
    
    //Bind BitCompressionMethod
    py::native_enum<bit7z::BitCompressionMethod>(mod, "BitCompressionMethod")
        .value("Deflate", bit7z::BitCompressionMethod::Deflate)
        .value("Deflate64", bit7z::BitCompressionMethod::Deflate64)
        .value("LZMA", bit7z::BitCompressionMethod::Lzma)
        .value("LZMA2", bit7z::BitCompressionMethod::Lzma2)
        .value("PPMD", bit7z::BitCompressionMethod::Ppmd)
        .value("Copy", bit7z::BitCompressionMethod::Copy)
        .value("BZip2", bit7z::BitCompressionMethod::BZip2)
        .export_values()
        .finalize();
    
    //Bind BitError
    py::native_enum<bit7z::BitError>(mod, "BitError")
        .value("Fail", bit7z::BitError::Fail)
        .value("FilterNotSpecified", bit7z::BitError::FilterNotSpecified)
        .value("FormatFeatureNotSupported", bit7z::BitError::FormatFeatureNotSupported)
        .value("IndicesNotSpecified", bit7z::BitError::IndicesNotSpecified)
        .value("InvalidArchivePath", bit7z::BitError::InvalidArchivePath)
        .value("InvalidOutputBufferSize", bit7z::BitError::InvalidOutputBufferSize)
        .value("InvalidCompressionMethod", bit7z::BitError::InvalidCompressionMethod)
        .value("InvalidDictionarySize", bit7z::BitError::InvalidDictionarySize)
        .value("InvalidIndex", bit7z::BitError::InvalidIndex)
        .value("InvalidWordSize", bit7z::BitError::InvalidWordSize)
        .value("ItemIsAFolder", bit7z::BitError::ItemIsAFolder)
        .value("ItemMarkedAsDeleted", bit7z::BitError::ItemMarkedAsDeleted)
        .value("NoMatchingItems", bit7z::BitError::NoMatchingItems)
        .value("NoMatchingSignature", bit7z::BitError::NoMatchingSignature)
        .value("NonEmptyOutputBuffer", bit7z::BitError::NonEmptyOutputBuffer)
        .value("NullOutputBuffer", bit7z::BitError::NullOutputBuffer)
        .value("RequestedWrongVariantType", bit7z::BitError::RequestedWrongVariantType)
        .value("UnsupportedOperation", bit7z::BitError::UnsupportedOperation)
        .value("UnsupportedVariantType", bit7z::BitError::UnsupportedVariantType)
        .value("WrongUpdateMode", bit7z::BitError::WrongUpdateMode)
        .value("InvalidZipPassword", bit7z::BitError::InvalidZipPassword)
        .export_values()
        .finalize();

    //Bind BitFaliureSource
    py::native_enum<bit7z::BitFailureSource>(mod, "BitFailureSource")
        .value("CRCError", bit7z::BitFailureSource::CRCError)
        .value("DataAfterEnd", bit7z::BitFailureSource::DataAfterEnd)
        .value("DataError", bit7z::BitFailureSource::DataError)
        .value("InvalidArchive", bit7z::BitFailureSource::InvalidArchive)
        .value("InvalidArgument", bit7z::BitFailureSource::InvalidArgument)
        .value("FormatDetectionError", bit7z::BitFailureSource::FormatDetectionError)
        .value("HeadersError", bit7z::BitFailureSource::HeadersError)
        .value("NoSuchItem", bit7z::BitFailureSource::NoSuchItem)
        .value("OperationNotSupported", bit7z::BitFailureSource::OperationNotSupported)
        .value("OperationNotPermitted", bit7z::BitFailureSource::OperationNotPermitted)
        .value("UnavailableData", bit7z::BitFailureSource::UnavailableData)
        .value("UnexpectedEnd", bit7z::BitFailureSource::UnexpectedEnd)
        .value("WrongPassword", bit7z::BitFailureSource::WrongPassword)
        .export_values()
        .finalize();
}