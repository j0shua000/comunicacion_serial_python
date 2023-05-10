import time
from datetime import datetime
from w1thermsensor import W1ThermSensor

class TemperatureSensor:
    def __init__(self, interval=30, average_interval=300, output_file="temperature_data.txt"):
        self.sensor = W1ThermSensor()
        self.interval = interval
        self.average_interval = average_interval
        self.output_file = output_file

    def read_temperature(self):
        return self.sensor.get_temperature()

    def log_temperature(self, temperature, timestamp):
        print(f"{timestamp}: Temperatura: {temperature}°C")

    def save_average_temperature(self, average_temperature, timestamp):
        with open(self.output_file, "a") as f:
            f.write(f"{timestamp}: Temperatura promedio: {average_temperature}°C\n")
        print(f"{timestamp}: Temperatura promedio guardada: {average_temperature}°C")

    def run(self):
        temperatures = []
        start_time = time.time()

        while True:
            current_time = time.time()
            elapsed_time = current_time - start_time

            temperature = self.read_temperature()
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            self.log_temperature(temperature, timestamp)

            temperatures.append(temperature)

            if elapsed_time >= self.average_interval:
                average_temperature = sum(temperatures) / len(temperatures)
                self.save_average_temperature(average_temperature, timestamp)
                temperatures = []
                start_time = time.time()

            time.sleep(self.interval)

def main():
    temperature_sensor = TemperatureSensor()
    temperature_sensor.run()

if __name__ == "__main__":
    main()
