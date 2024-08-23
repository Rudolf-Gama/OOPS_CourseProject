# OOPS_CourseProject

## Sport Event Management System

### Overview
The Sport Event Management System is a C++ application designed to handle various aspects of event management. It includes functionality for creating events, adding participants, issuing tickets, setting schedules, recording results, and displaying event details. The system uses Object-Oriented Programming (OOP) principles and includes features like factory patterns and singleton design patterns.

### Features
- **Event Creation**: Create new events with unique IDs, names, and dates.
- **Participant Management**: Add athletes and officials to events. Includes capacity limits for participants.
- **Ticket Management**: Issue and manage tickets for events. Includes ticket ID, holder name, seat number, and price.
- **Schedule Management**: Create and manage event schedules. Uses a Singleton pattern for schedule management.
- **Result Management**: Record and display event results with a medal tally for different countries.
- **Detailed Views**: Display detailed information about events, participants, tickets, schedules, and results.

### Classes
- **Result**: Represents the result of an event.
- **MedalTally**: Inherits from Result and tracks medal counts for countries.
- **Person**: Base class for different types of people (e.g., Athlete, Official).
- **Athlete**: Represents an athlete participating in events.
- **Official**: Represents an official with assigned tasks.
- **Ticket**: Represents a ticket issued for an event.
- **Schedule**: Represents the schedule for an event.
- **ScheduleManager**: Singleton class managing event schedules.
- **Event**: Represents an event including participants, tickets, and results.
- **PersonFactory, TicketFactory, ScheduleFactory**: Factory interfaces for creating Person, Ticket, and Schedule objects.
- **AthleteFactory, OfficialFactory, StandardTicketFactory, StandardScheduleFactory**: Concrete factories for creating specific types of objects.

### Usage

#### Build and Run the Project
Compile and Execute the project using a C++ compiler. For example, using `g++`:
```bash
g++ -o event_management Event_Management.cpp

./event_management

