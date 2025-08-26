#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <chrono>

// IoT Device Simulator Configuration
const int DEVICE_COUNT = 5;
const std::string DEVICE_TYPES[] = {"Temperature Sensor", "Humidity Sensor", "Light Sensor", "Motion Sensor", "Audio Sensor"};
const std::string DEVICE_NAMES[] = {"TS-001", "HS-001", "LS-001", "MS-001", "AS-001"};

// IoT Device Simulator Class
class IoTDevice {
public:
    std::string deviceType;
    std::string deviceName;
    int deviceId;
    double currentValue;

    IoTDevice(int id, std::string type, std::string name) {
        deviceId = id;
        deviceType = type;
        deviceName = name;
        currentValue = 0.0;
    }

    void simulate() {
        while (true) {
            currentValue = generateValue();
            std::cout << "Device " << deviceName << " (" << deviceType << ") reading: " << currentValue << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    }

private:
    double generateValue() {
        // Simulate generating a random value for the device
        return (double)rand() / RAND_MAX * 100.0;
    }
};

int main() {
    std::map<int, IoTDevice*> devices;

    // Initialize IoT devices
    for (int i = 0; i < DEVICE_COUNT; i++) {
        devices[i] = new IoTDevice(i, DEVICE_TYPES[i], DEVICE_NAMES[i]);
    }

    // Start IoT devices
    std::vector<std::thread> threads;
    for (auto& device : devices) {
        threads.emplace_back(&IoTDevice::simulate, device.second);
    }

    // Wait for all threads to finish
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}