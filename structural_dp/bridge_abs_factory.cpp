// Created by Camilo Castillo on 28/02/2024
// Bridge Pattern: combined with the abstract factory.

#include <iostream>
#include <memory>

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

class DeviceFactory
{
    public:
        virtual std::unique_ptr<Device> create_device() const = 0;
        virtual std::unique_ptr<Remote> create_remote(std::unique_ptr<Device>& device) const = 0;
        virtual ~DeviceFactory() = default;
};

class TVFactory : public DeviceFactory
{
    public:
        std::unique_ptr<Device> create_device() const override
        {
            return std::make_unique<TV>();
        }

        std::unique_ptr<Remote> create_remote(std::unique_ptr<Device>& device) const override
        {
            return std::make_unique<Remote>(device.get());
        }

        ~TVFactory() override = default;
};

class RadioFactory : public DeviceFactory
{
    public:
        std::unique_ptr<Device> create_device() const override
        {
            return std::make_unique<Radio>();
        }

        std::unique_ptr<Remote> create_remote(std::unique_ptr<Device>& device) const override
        {
            return std::make_unique<AdvancedRemote>(device.get());
        }

        ~RadioFactory() override = default;
};

//------------------------------------------------------------------------------

int main()
{
    TVFactory tvFactory;
    std::unique_ptr<Device> tv = tvFactory.create_device();
    std::unique_ptr<Remote> tvRemote = tvFactory.create_remote(tv);

    std::cout << "\n\nTV is " << (tv->is_enabled() ? "enabled" : "disabled") << std::endl;
    tvRemote->toggle_power();
    std::cout << "TV is " << (tv->is_enabled() ? "enabled" : "disabled") << std::endl;
    std::cout << "TV volume: " << tv->get_volume() << std::endl;
    tvRemote->volume_up();
    tvRemote->volume_up();
    std::cout << "TV volume: " << tv->get_volume() << std::endl;
    tvRemote->volume_down();
    std::cout << "TV volume: " << tv->get_volume() << std::endl;

    RadioFactory radioFactory;
    std::unique_ptr<Device> radio = radioFactory.create_device();
    AdvancedRemote radioRemote(radio.get());

    std::cout << "\n\nRadio is " << (radio->is_enabled() ? "enabled" : "disabled") << std::endl;
    radioRemote.toggle_power();
    std::cout << "Radio is " << (radio->is_enabled() ? "enabled" : "disabled") << std::endl;
    std::cout << "Radio volume: " << radio->get_volume() << std::endl;
    radioRemote.volume_up();
    radioRemote.volume_up();
    std::cout << "Radio volume: " << radio->get_volume() << std::endl;
    radioRemote.volume_down();
    std::cout << "Radio volume: " << radio->get_volume() << std::endl;
    radioRemote.mute();
    std::cout << "Radio volume: " << radio->get_volume() << std::endl;

    return 0;
}

//------------------------------------------------------------------------------
