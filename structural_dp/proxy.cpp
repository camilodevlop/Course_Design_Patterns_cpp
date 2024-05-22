// Created by Camilo Castillo on 20/05/2024
// Proxy Pattern

#include <iostream>
#include <ostream>
#include <tuple>
#include <map>

//------------------------------------------------------------------------------

class Video
{
    public:
        Video() = default;
        Video(std::string name, int id, std::string format)
             : video_(name, id, format) {} 
        
        std::string getVideoName() const { return std::get<0>(video_); }

        std::tuple<std::string, int, std::string> getVideoInfo(int id)
        {
            if(std::get<1>(video_) == id) return video_;

            std::cout << "Video not found" << std::endl;
            return std::make_tuple("", 0, "");
        }

        Video downloadVideo(int id)
        {
            if(std::get<1>(video_) == id)
                return *this;
            else
            {
                std::cout << "Video not found" << std::endl;
                return Video();
            }
        }

        ~Video() = default;

    private:
    std::tuple<std::string, int, std::string> video_;
};

//------------------------------------------------------------------------------

class ThirdPartyYoutubeLib
{
    public:
        virtual std::vector<std::string> listVideos() = 0;
        virtual std::tuple<std::string, int, std::string> getVideoInfo(int) = 0;
        virtual Video downloadVideo(int) = 0;
        virtual ~ThirdPartyYoutubeLib() = default;
};

//------------------------------------------------------------------------------

class ThirdPartyYoutubeClass: public ThirdPartyYoutubeLib
{
    public:
        ThirdPartyYoutubeClass() = default;

        void addVideo(std::string name, int id, std::string format)
        {
            videos_[id] = Video(name, id, format);
        }

        std::vector<std::string> listVideos() override
        {
            std::vector<std::string> videoList;
            for(const auto& video : videos_)
                videoList.push_back(video.second.getVideoName());
            return videoList;
        }
        
        std::tuple<std::string, int, std::string> getVideoInfo(int id) override
        {
            auto it = videos_.find(id);
            if(it != videos_.end())
                return it->second.getVideoInfo(id);
            else
            {
                std::cout << "Video not found" << std::endl;
                return std::make_tuple("", 0, "");
            }
        }

        Video downloadVideo(int id) override
        {
            auto it = videos_.find(id);
            if(it != videos_.end())
                return it->second.downloadVideo(id);
            else
            {
                std::cout << "Video not found" << std::endl;
                return Video();
            }
        }

        ~ThirdPartyYoutubeClass() override { videos_.clear(); }

    private:
        std::map<int, Video> videos_;
};

//------------------------------------------------------------------------------

class CachedYoutubeClass: public ThirdPartyYoutubeLib
{
    public:
        CachedYoutubeClass(ThirdPartyYoutubeLib* service): service_(service) {}

        std::vector<std::string> listVideos() override
        {
            if(videoList_.empty())
                std::cout << "Video list not cached" << std::endl;
                videoList_ = service_->listVideos();
            return videoList_;
        }

        std::tuple<std::string, int, std::string> getVideoInfo(int id) override
        {
            if(videoInfo_ == std::make_tuple("", 0, ""))
            {
                std::cout << "Video info not cached" << std::endl;
                videoInfo_ = service_->getVideoInfo(id);
            }
            return videoInfo_;
        }

        Video downloadVideo(int id) override
        {
            if(video_.getVideoName().empty())
            {
                std::cout << "Video not cached" << std::endl;
                video_ = service_->downloadVideo(id);
            }
            return video_;
        }

        ~CachedYoutubeClass() override = default;

    private:
        ThirdPartyYoutubeLib* service_;
        std::vector<std::string> videoList_;
        std::tuple<std::string, int, std::string> videoInfo_;
        Video video_;
};

//------------------------------------------------------------------------------

int main()
{
    ThirdPartyYoutubeClass youtubeService;
    CachedYoutubeClass youtubeProxy(&youtubeService);

    // Adding videos to the service
    youtubeService.addVideo("Video 1", 1, "mp4");
    youtubeService.addVideo("Video 2", 2, "avi");
    youtubeService.addVideo("Video 3", 3, "mkv");
    youtubeService.addVideo("Video 4", 4, "flv");
    youtubeService.addVideo("Video 5", 5, "mov");
    youtubeService.addVideo("Video 6", 6, "wmv");
    youtubeService.addVideo("Video 7", 7, "mpg");

    std::cout << "\n\nFirst call to listVideos()" << std::endl;
    std::vector<std::string > videoList = youtubeProxy.listVideos();
    for(const auto& video : videoList)
        std::cout << video << std::endl;

    std::cout << "\nSecond call to listVideos()" << std::endl;
    videoList = youtubeProxy.listVideos();
    for(const auto& video : videoList)
        std::cout << video << std::endl;

    std::cout << "\n\nFirst call to getVideoInfo()" << std::endl;
    std::tuple<std::string, int, std::string> videoInfo = youtubeProxy.getVideoInfo(7);
    std::cout << "Video name: " << std::get<0>(videoInfo) << std::endl;

    std::cout << "\nSecond call to getVideoInfo()" << std::endl;
    videoInfo = youtubeProxy.getVideoInfo(7);
    std::cout << "Video name: " << std::get<0>(videoInfo) << std::endl;

    std::cout << "\n\nFirst call to downloadVideo()" << std::endl;
    Video video = youtubeProxy.downloadVideo(5);
    std::cout << "Video name: " << video.getVideoName() << std::endl;

    std::cout << "\nSecond call to downloadVideo()" << std::endl;
    video = youtubeProxy.downloadVideo(5);
    std::cout << "Video name: " << video.getVideoName() << std::endl;

    return 0;
}

//------------------------------------------------------------------------------
