// Created by Camilo Castillo on 28/02/2024
// Bridge Pattern

#include <iostream>

//------------------------------------------------------------------------------

class Device
{
    public:
        virtual void enable() = 0;
        virtual void disable() = 0;
        virtual bool is_enabled() const = 0;
        virtual int get_volume() const = 0;
        virtual void set_volume(int volume) = 0;
        virtual ~Device() = default;
};

//------------------------------------------------------------------------------

class TV : public Device
{
    public:
        TV() : volume_(0), enabled_(false) {}
        void enable() override { enabled_ = true; }
        void disable() override { enabled_ = false; }
        bool is_enabled() const override { return enabled_; }
        int get_volume() const override { return volume_; }
        void set_volume(int volume) override { volume_ = volume; }
        ~TV() override = default;

    private:
        int volume_;
        bool enabled_;
};

class Radio : public Device
{
    public:
        Radio() : volume_(0), enabled_(false) {}
        void enable() override { enabled_ = true; }
        void disable() override { enabled_ = false; }
        bool is_enabled() const override { return enabled_; }
        int get_volume() const override { return volume_; }
        void set_volume(int volume) override { volume_ = volume; }
        ~Radio() override = default;

    private:
        int volume_;
        bool enabled_;
};

//------------------------------------------------------------------------------

class Remote
{
    public:
        Remote(Device* device) : device_(device) {}

        void toggle_power()
            { 
                if (device_->is_enabled()) 
                    device_->disable(); 
                else 
                    device_->enable(); 
            }

        void volume_up() 
        { 
            if (device_ -> is_enabled() && device_->get_volume() < 100)
                device_->set_volume(device_->get_volume() + 10);
        }

        void volume_down() 
        { 
            if (device_ -> is_enabled() && device_->get_volume() > 0)
                device_->set_volume(device_->get_volume() - 10); 
        }

        ~Remote() = default;

    protected:
        Device* device_;
};

class AdvancedRemote : public Remote
{
    public:
        AdvancedRemote(Device* device) : Remote(device) {}
        void mute() 
        { 
            if (device_->is_enabled())
                device_->set_volume(0); 
        }

        ~AdvancedRemote() = default;
};

//------------------------------------------------------------------------------

int main()
{
    TV tv;
    Radio radio;

    std::cout << "\nTV" << std::endl;

    Remote remoteTV(&tv);
    std::cout << "TV is " << (tv.is_enabled() ? "on" : "off") << std::endl;
    remoteTV.toggle_power();
    std::cout << "TV is " << (tv.is_enabled() ? "on" : "off") << std::endl;
    remoteTV.volume_up();
    std::cout << "TV volume: " << tv.get_volume() << std::endl;
    remoteTV.volume_down();
    std::cout << "TV volume: " << tv.get_volume() << std::endl;

    std::cout << "\nTV: crotrolled by an advancedRemoteTV" << std::endl;
    AdvancedRemote advancedRemoteTV(&tv);
    std::cout << "TV is " << (tv.is_enabled() ? "on" : "off") << std::endl;
    advancedRemoteTV.volume_up();
    std::cout << "TV volume: " << tv.get_volume() << std::endl;
    advancedRemoteTV.volume_down();
    std::cout << "TV volume: " << tv.get_volume() << std::endl;
    advancedRemoteTV.mute();
    std::cout << "TV volume: " << tv.get_volume() << std::endl;

    std::cout << "\nRadio" << std::endl;

    Remote remoteRadio(&radio);
    std::cout << "Radio is " << (radio.is_enabled() ? "on" : "off") << std::endl;
    remoteRadio.toggle_power();
    std::cout << "Radio is " << (radio.is_enabled() ? "on" : "off") << std::endl;
    remoteRadio.volume_up();
    std::cout << "Radio volume: " << radio.get_volume() << std::endl;
    remoteRadio.volume_down();
    std::cout << "Radio volume: " << radio.get_volume() << std::endl;

    std::cout << "\nRadio: crotrolled by an advancedRemoteRadio" << std::endl;
    AdvancedRemote advancedRemoteRadio(&radio);
    std::cout << "Radio is " << (radio.is_enabled() ? "on" : "off") << std::endl;
    advancedRemoteRadio.volume_up();
    std::cout << "Radio volume: " << radio.get_volume() << std::endl;
    advancedRemoteRadio.volume_down();
    std::cout << "Radio volume: " << radio.get_volume() << std::endl;
    advancedRemoteRadio.mute();
    std::cout << "Radio volume: " << radio.get_volume() << std::endl;

    return 0;
}

//------------------------------------------------------------------------------
