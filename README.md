# ESP32 Smart Rain Alert with Telegram Bot

A smart IoT system that alerts users before rain and responds to weather queries via Telegram chat.

## Features
- Sends alert if rain is predicted
- Responds to "weather" command on Telegram
- Uses OpenWeatherMap API and Telegram Bot API

## Components
- ESP32 Development Board
- Wi-Fi connection
- OpenWeatherMap API Key
- Telegram Bot Token and Chat ID

## Setup Instructions

1. Clone this repo
2. Get your OpenWeatherMap API key
3. Create a Telegram bot using @BotFather
4. Edit `main.ino` and replace:
   - `YOUR_WIFI`, `YOUR_PASSWORD`
   - `YOUR_API_KEY`
   - `YOUR_BOT_TOKEN`
   - `YOUR_CHAT_ID`
5. Upload to ESP32 using Arduino IDE

## How It Works
- ESP32 connects to Wi-Fi
- Checks weather from OpenWeatherMap
- If rain is expected, sends a Telegram message
- Also responds to manual "weather" messages

## Demo
![Telegram Screenshot](screenshot.png)

## Future Improvements
- Add local sensors
- Add 3-day forecasts
- Auto push updates

## License
MIT
