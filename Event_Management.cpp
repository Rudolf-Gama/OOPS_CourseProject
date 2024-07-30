#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <unordered_map>

using namespace std;

const int MAX_EVENTS = 10;
const int MAX_PARTICIPANTS = 20;
const int MAX_TICKETS = 20;


void displayMenu() {
    cout << "1. Create Event\n";
    cout << "2. Add Participant to Event\n";
    cout << "3. Add Ticket to Event\n";
    cout << "4. Set Event Schedule\n";
    cout << "5. Set Event Result\n";
    cout << "6. Display Event Details\n";
    cout << "7. Exit\n";
    cout << "Enter your choice: ";
}

class Result {
public:
    int result_id;
    string event;
    int position;
    float time_score, points_score;

    Result(int id, string e, int pos, float time, float points)
        : result_id(id), event(e), position(pos), time_score(time), points_score(points) {}

    virtual void getResult() const {
        cout << "Result ID: " << result_id << ", Event: " << event << ", Position: " << position
             << ", Time Score: " << time_score << ", Points Score: " << points_score << endl;
    }

    virtual void recordResult(int pos, float time, float points) {
        position = pos;
        time_score = time;
        points_score = points;
    }
};

class MedalTally : public Result {
public:
    string country;
    int gold, silver, bronze, total;

    MedalTally(int id, string e, int pos, float time, float points, string c)
        : Result(id, e, pos, time, points), country(c), gold(0), silver(0), bronze(0), total(0) {
        updateTallyForPosition(pos);
    }

    void updateTallyForPosition(int pos) {
        switch (pos) {
            case 1:
                gold++;
                break;
            case 2:
                silver++;
                break;
            case 3:
                bronze++;
                break;
        }
        total = gold + silver + bronze;
    }

    void getResult() const override {
        Result::getResult();
        cout << "Country: " << country << ", Gold: " << gold << ", Silver: " << silver
             << ", Bronze: " << bronze << ", Total: " << total << endl;
    }

    void recordResult(int pos, float time, float points) override {
        Result::recordResult(pos, time, points);
        updateTallyForPosition(pos);
    }
};

class Person {
public:
    string name;
    int age;
    string country;
    int id;

    Person(string n, int a, string c, int i) : name(n), age(a), country(c), id(i) {}

    virtual void getDetails() const {
        cout << "Name: " << name << ", Age: " << age << ", Country: " << country << ", ID: " << id << endl;
    }
};

class Athlete : public Person {
public:
    vector<string> events_participated;
    int medals_won;

    Athlete(string n, int a, string c, int i) : Person(n, a, c, i), medals_won(0) {}

    void registerAthlete(string event) {
        if (events_participated.size() < MAX_EVENTS) {
            events_participated.push_back(event);
        } else {
            throw overflow_error("Athlete event capacity reached!");
        }
    }

    void getDetails() const override {
        cout << "Role: Athlete\n";
        Person::getDetails();
    }
};

class Official : public Person {
public:
    string assigned_task;

    Official(string n, int a, string c, int i) : Person(n, a, c, i) {}

    void assignTask(string task) {
        assigned_task = task;
    }

    void getDetails() const override {
        cout << "Role: Official\n";
        cout << "Assigned Task: " << assigned_task << endl;
        Person::getDetails();
    }
};

class Ticket {
public:
    int ticket_id;
    string holder_name, event_name;
    int seat_no;
    float price;

    Ticket(int id, string holder, string event, int seat, float p) : ticket_id(id), holder_name(holder), event_name(event), seat_no(seat), price(p) {}

    void issueTicket() const {
        cout << "Ticket issued to " << holder_name << " for event " << event_name << " at seat " << seat_no << "." << endl;
    }

    void getDetails() const {
        cout << "Ticket ID: " << ticket_id << ", Holder Name: " << holder_name << ", Event Name: " << event_name << ", Seat No: " << seat_no << ", Price: " << price << endl;
    }
};

class Schedule {
public:
    int schedule_id;
    string event;
    string start_date, end_date;

    Schedule(int id, string e, string start, string end) : schedule_id(id), event(e), start_date(start), end_date(end) {}

    void createSchedule() const {
        cout << "Schedule created for event " << event << " from " << start_date << " to " << end_date << "." << endl;
    }

    void getSchedule() const {
        cout << "Schedule ID: " << schedule_id << ", Event: " << event << ", Start Date: " << start_date << ", End Date: " << end_date << endl;
    }
};

class ScheduleManager {
private:
    static ScheduleManager* instance;
    unordered_map<int, Schedule*> schedules;

    ScheduleManager() {}

public:
    static ScheduleManager* getInstance() {
        if (instance == nullptr) {
            instance = new ScheduleManager();
        }
        return instance;
    }

    void createSchedule(int id, string event, string start_date, string end_date) {
        if (schedules.find(id) != schedules.end()) {
            throw runtime_error("Schedule already exists!");
        }
        schedules[id] = new Schedule(id, event, start_date, end_date);
    }

    Schedule* getSchedule(int id) const {
        auto it = schedules.find(id);
        if (it == schedules.end()) {
            throw runtime_error("No schedule exists with the given ID!");
        }
        return it->second;
    }

    void deleteSchedule(int id) {
        auto it = schedules.find(id);
        if (it != schedules.end()) {
            delete it->second;
            schedules.erase(it);
        }
    }

    ~ScheduleManager() {
        for (auto& pair : schedules) {
            delete pair.second;
        }
    }
};

ScheduleManager* ScheduleManager::instance = nullptr;

// Factory Interfaces
class PersonFactory {
public:
    virtual Person* createPerson(const string& name, int age, const string& country, int id) = 0;
};

class TicketFactory {
public:
    virtual Ticket* createTicket(int ticket_id, const string& holder_name, const string& event_name, int seat_no, float price) = 0;
};

class ScheduleFactory {
public:
    virtual Schedule* createSchedule(int id, const string& event, const string& start, const string& end) = 0;
};

// Concrete Factories
class AthleteFactory : public PersonFactory {
public:
    Person* createPerson(const string& name, int age, const string& country, int id) override {
        return new Athlete(name, age, country, id);
    }
};

class OfficialFactory : public PersonFactory {
public:
    Person* createPerson(const string& name, int age, const string& country, int id) override {
        return new Official(name, age, country, id);
    }
};

class StandardTicketFactory : public TicketFactory {
public:
    Ticket* createTicket(int ticket_id, const string& holder_name, const string& event_name, int seat_no, float price) override {
        return new Ticket(ticket_id, holder_name, event_name, seat_no, price);
    }
};

class StandardScheduleFactory : public ScheduleFactory {
public:
    Schedule* createSchedule(int id, const string& event, const string& start, const string& end) override {
        return new Schedule(id, event, start, end);
    }
};

class Event {
public:
    int event_id;
    string event_name, date;
    vector<Person*> participants;
    vector<Ticket*> tickets;
    Result* result;
    Schedule* schedule;

    Event(int id, string e, string d)
        : event_id(id), event_name(e), date(d), result(nullptr), schedule(nullptr) {}

    void addParticipant(Person* person) {
        if (participants.size() < MAX_PARTICIPANTS) {
            participants.push_back(person);
        } else {
            throw overflow_error("Participant capacity reached!");
        }
    }

    void setResult(Result* r) {
        result = r;
    }

    void setSchedule(int schedule_id) {
        schedule = ScheduleManager::getInstance()->getSchedule(schedule_id);
    }

    void addTicket(Ticket* t) {
        if (tickets.size() < MAX_TICKETS) {
            tickets.push_back(t);
        } else {
            throw overflow_error("Ticket capacity reached!");
        }
    }

    void getDetails() const {
        cout << "Event ID: " << event_id << ", Event Name: " << event_name << ", Date: " << date << endl;
        cout << "Participants: " << endl;
        for (Person* p : participants) {
            p->getDetails();
        }
        cout << "Tickets: " << endl;
        for (Ticket* t : tickets) {
            t->getDetails();
        }
        cout << "Schedule: " << endl;
        if (schedule) {
            schedule->getSchedule();
        } else {
            cout << "No schedule set." << endl;
        }
        cout << "Result: " << endl;
        if (result) {
            result->getResult();
        } else {
            cout << "No result recorded." << endl;
        }
    }

    ~Event() {
        for (Person* p : participants) {
            delete p;
        }
        for (Ticket* t : tickets) {
            delete t;
        }
        delete result;
    }
};

int main() {
    vector<Event> events;
    AthleteFactory athleteFactory;
    OfficialFactory officialFactory;
    StandardTicketFactory ticketFactory;

    while (true) {
        displayMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, date;
            cout << "Enter event ID, name, and date: ";
            cin >> id >> name >> date;
            try {
                events.emplace_back(id, name, date);
                cout << "Event created successfully." << endl;
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        } else if (choice == 2) {
            int event_id, person_type, age, id;
            string name, country;
            cout << "Enter event ID: ";
            cin >> event_id;
            cout << "Enter person type (1 for Athlete, 2 for Official): ";
            cin >> person_type;
            cout << "Enter name, age, country, and ID: ";
            cin >> name >> age >> country >> id;
            try {
                if (person_type == 1) {
                    events[event_id - 1].addParticipant(athleteFactory.createPerson(name, age, country, id));
                } else {
                    events[event_id - 1].addParticipant(officialFactory.createPerson(name, age, country, id));
                }
                cout << "Participant added successfully." << endl;
            } catch (const overflow_error& e) {
                cout << "Error: " << e.what() << endl;
            } catch (const exception& e) {
                cout << "An error occurred: " << e.what() << endl;
            }
        } else if (choice == 3) {
            int event_id, ticket_id, seat_no;
            float price;
            string holder_name, event_name;
            cout << "Enter event ID: ";
            cin >> event_id;
            cout << "Enter ticket ID, holder name, seat number, and price: ";
            cin >> ticket_id >> holder_name >> seat_no >> price;
            try {
                events[event_id - 1].addTicket(ticketFactory.createTicket(ticket_id, holder_name, events[event_id - 1].event_name, seat_no, price));
                cout << "Ticket added successfully." << endl;
            } catch (const overflow_error& e) {
                cout << "Error: " << e.what() << endl;
            } catch (const exception& e) {
                cout << "An error occurred: " << e.what() << endl;
            }
        } else if (choice == 4) {
            int event_id, schedule_id;
            string start_date, end_date;
            cout << "Enter event ID and schedule ID: ";
            cin >> event_id >> schedule_id;
            cout << "Enter start and end dates: ";
            cin >> start_date >> end_date;
            try {
                ScheduleManager::getInstance()->createSchedule(schedule_id, events[event_id - 1].event_name, start_date, end_date);
                events[event_id - 1].setSchedule(schedule_id);
                cout << "Schedule set successfully." << endl;
            } catch (const runtime_error& e) {
                cout << "Error: " << e.what() << endl;
            } catch (const exception& e) {
                cout << "An error occurred: " << e.what() << endl;
            }
        } else if (choice == 5) {
            int event_id, result_id, pos;
            float time_score, points_score;
            string event, country;
            cout << "Enter event ID: ";
            cin >> event_id;
            cout << "Enter result ID, position, time score, points score, and country: ";
            cin >> result_id >> pos >> time_score >> points_score >> country;
            try {
                events[event_id - 1].setResult(new MedalTally(result_id, events[event_id - 1].event_name, pos, time_score, points_score, country));
                cout << "Result set successfully." << endl;
            } catch (const exception& e) {
                cout << "An error occurred: " << e.what() << endl;
            }
        } else if (choice == 6) {
            int event_id;
            cout << "Enter event ID: ";
            cin >> event_id;
            try {
                events[event_id - 1].getDetails();
            } catch (const exception& e) {
                cout << "Error: " << e.what() << endl;
            }
        } else if (choice == 7) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

