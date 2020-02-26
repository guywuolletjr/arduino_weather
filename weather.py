from pyowm import OWM
import serial
import click
import time

API_KEY = 'f25b71fd991524f71ad191e02a39d40e'
PORT = '/dev/cu.usbserial-DJ00S6Q0'

@click.command()
@click.option('-z', '--zip-code', default='94305', type=str, help='Zip code to return weather data for')
@click.option('-f', '--fahrenheit', is_flag=True, default=True, help='Return temperature in fahrenheit.')
@click.option('-c', '--celsius', is_flag=True, default=False, help='Return temperature in fahrenheit.')

def get_weather(zip_code, fahrenheit, celsius):

    #some validation on the zip code
    if( (len(zip_code) != 5) or  not zip_code.isdigit() ):
        print("Please enter a valid zip code")
        return

    owm = OWM(API_KEY)

    unit = 'fahrenheit'
    if(celsius): units = 'celsius'

    try:

        observation = owm.weather_at_zip_code(zip_code, "US")
        weather = observation.get_weather()

        temperature = weather.get_temperature(unit=unit)
        temp = temperature['temp']
        high_temp = temperature['temp_max']
        low_temp = temperature['temp_min']

        print("Temperature: {}".format(temp) )
        print("High for the day: {}".format(high_temp) )
        print("Low for the day: {}".format(low_temp) )

        int_temp = int(temp)

        # args are port as a str and baud rate
        arduino = serial.Serial(PORT, 115200)
        time.wait(2) # allow the arduino to listen on the port
        arduino.write("{}\n".format(int_temp))

    except Exception as e:
       # print (e)
       print("Open Weather Map was unable to identify the given zip code. Please enter a valid zip code.")

if __name__ == '__main__':
    get_weather()
