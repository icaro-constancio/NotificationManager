
# NotificationManager

## About the Project

This project simplifies sending notifications to different platforms (Gmail and Discord) using the `curl` library to perform the necessary HTTP and SMTP requests.

## Features

* **Discord Notification:** Sends messages to a Discord channel via configured webhook.  
* **Email Notification:** Sends emails through an SMTP server (currently configured for Gmail with an app password).  
* **Interactive Interface:** Terminal-based menu to select the type of notification.  
* **Environment Variable Configuration:** Uses environment variables to store sensitive credentials (webhooks, emails, passwords), improving security.

## Technologies Used

* **C++:** Main programming language.  
* **cURL:** Used to communicate with Discord and SMTP servers.  
* **Make:** Used during the build process inside the Docker container.  
* **Docker:** Platform for packaging and running the project in containers.

## Prerequisites

You need to have the following installed:

* Docker  
* Docker Compose

## Installation and Setup with Docker

The recommended way to use this project is via Docker, which encapsulates all necessary dependencies.

1. **Clone the repository:**
    ```
    git clone <https://github.com/icaro-constancio/NotificationManager.git>
    ```

2. **Set environment variables:**  
   Replace the values in the `.env` file with your own credentials:

    ```
    USER_EMAIL=your_email@gmail.com
    USER_PASSWORD=your_gmail_app_password
    RECIPIENT_EMAIL=recipient_email@example.com
    DISCORD_WEBHOOK=your_discord_webhook_url
    ```
    
    * **Important for Gmail:** If you're using Gmail, you'll need to generate an [app password](https://support.google.com/accounts/answer/185833?hl=en) in your Google security settings, since your regular account password may not work.

3. **Build the Docker image:**

    Inside the `NotificationManager` folder, run:
    ```
    docker-compose build notification-manager
    ```
    This command builds the Docker image for the `notification-manager` service without starting the container.

4. **Start the container in the background:**
    ```
    docker-compose up -d notification-manager
    ```
    This will start the container in *detached* mode, making it ready for use.

## How to Run the Application

With the `notification-manager-container` running in the background (after running `docker-compose up -d notification-manager`), you can interact with the application at any time:

1. **Access the container’s terminal:**
    ```
    docker exec -it notification-manager-container bash
    ```
    This takes you to the terminal inside the container, where the `notify` program is located.

2. **Run the `notify` program:**
    Inside the container terminal, run:
    ```
    ./notify
    ```
    You’ll see the interactive menu:
    ```
    Key d - Notify Discord
    Key e - Notify Email
    Key 0 - Exit

    Press a key:
    ```

3. **Exit the container terminal:**
    When you're done using the program, type `exit` and press Enter to leave the container terminal:
    ```
    exit
    ```
