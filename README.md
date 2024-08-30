# 🎉 Sport Event Management System

## 🌟 Overview
The **Sport Event Management System** is an advanced C++ application crafted to manage various aspects of sports events efficiently. From creating events and managing participants to handling ticketing, scheduling, and results, this system is built on solid Object-Oriented Programming (OOP) principles. It incorporates sophisticated design patterns like factory and singleton patterns to ensure scalability and robustness.

## 🛠️ Features
- 🎉 **Event Creation**: Seamlessly create and manage new events with unique IDs, names, and dates.
- 👥 **Participant Management**: Effortlessly add athletes and officials, manage their roles, and handle capacity limits.
- 🎫 **Ticket Management**: Issue, manage, and track tickets with details such as ticket ID, holder's name, seat number, and price.
- 🗓️ **Schedule Management**: Organize and manage event schedules with a Singleton pattern for centralized control.
- 🏅 **Result Management**: Record and showcase event results, including a detailed medal tally for participating countries.
- 📊 **Detailed Views**: Access comprehensive information on events, participants, tickets, schedules, and results in an intuitive interface.

## 📚 Classes
- **Result**: Represents the outcome of an event.
- **MedalTally**: Extends `Result` to track and display medal counts by country.
- **Person**: Base class for individuals involved in events (e.g., `Athlete`, `Official`).
- **Athlete**: Represents athletes participating in various events.
- **Official**: Represents officials with designated responsibilities and tasks.
- **Ticket**: Manages ticket information, including seat allocations and pricing.
- **Schedule**: Defines and organizes event timings and sequences.
- **ScheduleManager**: A Singleton class that oversees event schedules.
- **Event**: Manages the event's participants, tickets, and results.
- **PersonFactory, TicketFactory, ScheduleFactory**: Abstract factory interfaces for creating `Person`, `Ticket`, and `Schedule` objects.
- **AthleteFactory, OfficialFactory, StandardTicketFactory, StandardScheduleFactory**: Concrete factories for creating specific object types.

## 🚀 Usage

### Build and Run the Project
To compile and execute the project, use a C++ compiler like `g++`. Run the following commands:
```bash
g++ -o event_management Event_Management.cpp
./event_management
