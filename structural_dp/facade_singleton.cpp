// Created by Camilo Castillo on 08/05/2024
// Decorator Pattern: Decorator Facade Singleton

#include <iostream>
#include <memory>

//------------------------------------------------------------------------------

class VideoFile
{
    public:
        VideoFile(const std::string& filename): filename_(filename) {}

        std::string fileName() const { return filename_; }
        std::string compressionType() const { return compressionType_; }
        friend class OggCompressionCodec;
        friend class MPEG4CompressionCodec;

        ~VideoFile() = default;

    private:
        std::string filename_;
        std::string compressionType_{};
        void setCompressionType(std::string&& compressionType) 
        { compressionType_ = compressionType; }
};

class CodecFactory
{
    public:
        CodecFactory(VideoFile videoFile): videoFile_(videoFile) {}

        std::string extractCode() const
        {
            std::cout << "Extracting code from video file " << videoFile_.fileName() << std::endl;
            return "code";
        } 

        ~CodecFactory() = default;

    private:
        VideoFile videoFile_;
};

class OggCompressionCodec
{
    public:
        OggCompressionCodec() = default;

        void compress(VideoFile& videoFile) const
        {
            std::cout << "Compressing video file " << videoFile.fileName() 
                      << " using Ogg codec" << std::endl;
            videoFile.setCompressionType("ogg");
        }

        ~OggCompressionCodec() = default;
};

class MPEG4CompressionCodec
{
    public:
        MPEG4CompressionCodec() = default;

        void compress(VideoFile& videoFile) const
        {
            std::cout << "Compressing video file " << videoFile.fileName() 
                      << " using MPEG4 codec" << std::endl;
            videoFile.setCompressionType("mpeg4");
        }

        ~MPEG4CompressionCodec() = default;
};

//------------------------------------------------------------------------------

class VideoConverterSingleton
{
    public:
        static VideoConverterSingleton& instance()
        {
            static VideoConverterSingleton instance;
            return instance;
        }

        std::unique_ptr<VideoFile> convert(std::string&& filename, std::string&& format)
        {
            std::unique_ptr<VideoFile> videoFileConverted = std::make_unique<VideoFile>(filename);
            CodecFactory codecFactory(*videoFileConverted);

            if (format == "ogg")
            {
                OggCompressionCodec oggCodec;
                oggCodec.compress(*videoFileConverted);
            }
            else if (format == "mpeg4")
            {
                MPEG4CompressionCodec mpeg4Codec;
                mpeg4Codec.compress(*videoFileConverted);
            }
            
            return videoFileConverted;
        }

        ~VideoConverterSingleton() = default;

    private:
        VideoConverterSingleton() = default;
        VideoConverterSingleton(const VideoConverterSingleton&) = delete;
        VideoConverterSingleton& operator=(const VideoConverterSingleton&) = delete;
};

//------------------------------------------------------------------------------

int main()
{
    VideoConverterSingleton& videoConverter = VideoConverterSingleton::instance();
    std::unique_ptr<VideoFile> videoFile = videoConverter.convert("video.mp4", "ogg");

    std::cout << "Video file: " << videoFile->fileName() 
              << ", Compression type: " << videoFile->compressionType() 
              << std::endl;

    return 0;
}

//------------------------------------------------------------------------------
