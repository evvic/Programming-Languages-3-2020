#include <iostream>
#include "RANDOM.H"
#include "Utility.h"

//P5 added a CheckPlaneFuel() to decrement fuel level for each plane in queue waiting to land per unit time 



   // Section 3.1:
enum Plane_status { null, arriving, departing };

class Plane {
public:
    Plane();
    Plane(int flt, int time, Plane_status status, int fuel_level);
    void refuse() const;
    void land(int time) const;
    void fly(int time) const;
    int started() const;
    int getFuel();
    void updateFuel(int f);
    int getFlightNum();

private:
    int fuel;
    int flt_num;
    int clock_start;
    //int item, entry; Trying to find place for these to get rid of undeclared identifier
    Plane_status state;
};


typedef Plane Queue_entry;
const int max_int = INT_MAX;
enum Runway_activity { idle, land, takeoff_enum };
const int maxqueue = 10; //  small value for testing


class Queue {
public:
    Queue();
    bool empty() const;
    Error_code serve();
    Error_code append(const Queue_entry& item);
    Error_code retrieve(Queue_entry& item) const;

protected:
    int count;
    int front, rear;
    Queue_entry entry[maxqueue];
};


class Extended_queue : public Queue {
public:
    bool full() const;
    int size() const;
    void clear();
    Error_code serve_and_retrieve(Queue_entry& item);
};

Error_code Extended_queue::serve_and_retrieve(Queue_entry& item) {
    if (count <= 0) return underflow;
    item = entry[front];
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}


Queue::Queue()
/*
Post: The Queue is initialized to be empty.
*/
{
    count = 0;
    rear = maxqueue - 1;
    front = 0;
}


bool Queue::empty() const
/*
Post: Return true if the Queue is empty, otherwise return false.
*/
{
    return count == 0;
}


Error_code Queue::append(const Queue_entry& item)
/*
Post: item is added to the rear of the Queue. If the Queue is full
return an Error_code of overflow and leave the Queue unchanged.
*/

{
    if (count >= maxqueue) return overflow;
    count++;
    rear = ((rear + 1) == maxqueue) ? 0 : (rear + 1);
    entry[rear] = item;
    return success;
}


Error_code Queue::serve()
/*
Post: The front of the Queue is removed. If the Queue
is empty return an Error_code of underflow.
*/

{
    if (count <= 0) return underflow;
    count--;
    front = ((front + 1) == maxqueue) ? 0 : (front + 1);
    return success;
}


Error_code Queue::retrieve(Queue_entry& item) const
/*
Post: The front of the Queue retrieved to the output
      parameter item. If the Queue is empty return an Error_code of underflow.
*/

{
    if (count <= 0) return underflow;
    item = entry[front];
    return success;
}


int Extended_queue::size() const
/*
Post:   Return the number of entries in the Extended_queue.
*/
{
    return count;
}



class Runway {
public:
    Runway(int limit);
    Error_code can_land(const Plane& current);
    Error_code can_depart(const Plane& current);
    Runway_activity activity(int time, Plane& moving);
    void shut_down(int time) const;
    void CheckPlaneFuel(/*const Plane& current*/);

private:
    Extended_queue landing;
    Extended_queue takeoff_ext;
    int queue_limit;
    int num_land_requests;        //  number of planes asking to land
    int num_takeoff_requests;     //  number of planes asking to take off
    int num_landings;             //  number of planes that have landed
    int num_takeoffs;             //  number of planes that have taken off
    int num_land_accepted;        //  number of planes queued to land
    int num_takeoff_accepted;     //  number of planes queued to take off
    int num_land_refused;         //  number of landing planes refused
    int num_takeoff_refused;      //  number of departing planes refused
    int land_wait;                //  total time of planes waiting to land
    int takeoff_wait;             //  total time of planes waiting to take off
    int idle_time;                //  total time runway is idle
    int num_crashes;              //  total crashes waiting to land
};




void initialize(int& end_time, int& queue_limit,
    double& arrival_rate, double& departure_rate)
    /*
    Pre:  The user specifies the number of time units in the simulation,
          the maximal queue sizes permitted,
          and the expected arrival and departure rates for the airport.
    Post: The program prints instructions and initializes the parameters
          end_time, queue_limit, arrival_rate, and departure_rate to
          the specified values.
    Uses: utility function user_says_yes
    */

{
    cout << "This program simulates an airport with only one runway." << endl
        << "One plane can land or depart in each unit of time." << endl;
    cout << "Up to what number of planes can be waiting to land "
        << "or take off at any time? " << flush;
    cin >> queue_limit;

    cout << "How many units of time will the simulation run?" << flush;
    cin >> end_time;

    bool acceptable;
    do {
        cout << "Expected number of arrivals per unit time?" << flush;
        cin >> arrival_rate;
        cout << "Expected number of departures per unit time?" << flush;
        cin >> departure_rate;
        if (arrival_rate < 0.0 || departure_rate < 0.0)
            cerr << "These rates must be nonnegative." << endl;
        else
            acceptable = true;

        if (acceptable && arrival_rate + departure_rate > 1.0)
            cerr << "Safety Warning: This airport will become saturated. " << endl;

    } while (!acceptable);
}


Runway::Runway(int limit)
/*
Post:  The Runway data members are initialized to record no
       prior Runway use and to record the limit on queue sizes.
*/

{
    queue_limit = limit;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_refused = num_takeoff_refused = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
    num_crashes = 0;
}

void Runway::CheckPlaneFuel(/*const Plane& current*/) {
    /*
        Cycles through Plane queue and decrements fuel level for each plane
        Reorders queue for lowest fuel level priority
        Reports any planes that crashed for not having any fuel left
    */

    int tfuel;
    Plane tplane;

    Extended_queue priority_planes;
    Extended_queue other_planes;

    while (landing.serve_and_retrieve(tplane) == success) {
        tfuel = tplane.getFuel();
        tfuel--;
        tplane.updateFuel(tfuel);
        
        if(tfuel < 1) {
            //fuel = 0 = plane crashes
            cout << "Flight no. " << tplane.getFlightNum() << " ran out of fuel and crashed." << endl;
            tplane.refuse();
            num_crashes++;
        }
        else if (tfuel == 1) {
            //put in front of queue
            priority_planes.append(tplane);
        }
        else {
            //put in queue
            other_planes.append(tplane);
        }
        
    }
    //now fill original queue with the planes
    while (priority_planes.serve_and_retrieve(tplane) == success) {
        landing.append(tplane);
    }
    while (other_planes.serve_and_retrieve(tplane) == success) {
        landing.append(tplane);
    }
}

Error_code Runway::can_land(const Plane& current)
/*
Post:  If possible, the Plane current is added to the
       landing Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    

    Error_code result;
    if (landing.size() < queue_limit)
        result = landing.append(current);
    else
        result = fail;
    num_land_requests++;

    if (result != success)
        num_land_refused++;
    else
        num_land_accepted++;

    return result;
}


Error_code Runway::can_depart(const Plane& current)
/*
Post:  If possible, the Plane current is added to the
       takeoff Queue; otherwise, an Error_code of overflow is
       returned. The Runway statistics are updated.
Uses:  class Extended_queue.
*/

{
    Error_code result;
    if (takeoff_ext.size() < queue_limit)
        result = takeoff_ext.append(current);
    else
        result = fail;
    num_takeoff_requests++;
    if (result != success)
        num_takeoff_refused++;
    else
        num_takeoff_accepted++;

    return result;
}


Runway_activity Runway::activity(int time, Plane& moving)
/*
Post:  If the landing Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  land is returned. Otherwise,
       if the takeoff Queue has entries, its front
       Plane is copied to the parameter moving
       and a result  takeoff is returned. Otherwise,
       idle is returned. Runway statistics are updated.
Uses:  class Extended_queue.
*/


{
    Runway_activity in_progress;
    if (!landing.empty()) {
        landing.retrieve(moving);
        land_wait += time - moving.started();
        num_landings++;
        in_progress = land;
        landing.serve();
    }

    else if (!takeoff_ext.empty()) {
        takeoff_ext.retrieve(moving);
        takeoff_wait += time - moving.started();
        num_takeoffs++;
        in_progress = takeoff_enum; //maybe double takeoff variable
        takeoff_ext.serve();
    }

    else {
        idle_time++;
        in_progress = idle;
    }
    return in_progress;
}


Plane::Plane(int flt, int time, Plane_status status, int fuel_level)
/*
Post:  The Plane data members flt_num, clock_start,
       and state are set to the values of the parameters flt,
       time and status, respectively.
*/

{
    fuel = fuel_level;
    flt_num = flt;
    clock_start = time;
    state = status;
    cout << "Plane number " << flt << " ready to ";
    if (status == arriving)
        cout << "land." << endl;
    else
        cout << "take off." << endl;
}


Plane::Plane()
/*
Post:  The Plane data members flt_num, clock_start,
       state are set to illegal default values.
*/
{
    fuel = 5;
    flt_num = -1;
    clock_start = -1;
    state = null;
}

int Plane::getFuel() {
    return fuel;
}

void Plane::updateFuel(int f) {
    fuel = f;
}

int Plane::getFlightNum() {
    return flt_num;
}


void Plane::refuse() const
/*
Post: Processes a Plane wanting to use Runway, when
      the Queue is full.
*/

{
    cout << "Plane number " << flt_num;
    if (fuel <= 0) {
        cout << " crashed." << endl;
    }
    else {
        if (state == arriving)
            cout << " directed to another airport" << endl;
        else
            cout << " told to try to takeoff again later" << endl;
    }

}


void Plane::land(int time) const
/*
Post: Processes a Plane that is landing at the specified time.
*/

{
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " landed after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue with " << fuel << " fuel left." << endl;
}


void Plane::fly(int time) const
/*
Post: Process a Plane that is taking off at the specified time.
*/

{
    int wait = time - clock_start;
    cout << time << ": Plane number " << flt_num << " took off after "
        << wait << " time unit" << ((wait == 1) ? "" : "s")
        << " in the takeoff queue." << endl;
}


int Plane::started() const
/*
Post: Return the time that the Plane entered the airport system.
*/
{
    return clock_start;
}

void run_idle(int time)
/*
Post: The specified time is printed with a message that the runway is idle.
*/
{
    cout << time << ": Runway is idle." << endl;
}


void Runway::shut_down(int time) const
/*
Post: Runway usage statistics are summarized and printed.
*/

{
    cout << "Simulation has concluded after " << time << " time units." << endl
        << "Total number of planes processed "
        << (num_land_requests + num_takeoff_requests) << endl
        << "Total number of planes asking to land "
        << num_land_requests << endl
        << "Total number of planes asking to take off "
        << num_takeoff_requests << endl
        << "Total number of planes accepted for landing "
        << num_land_accepted << endl
        << "Total number of planes accepted for takeoff "
        << num_takeoff_accepted << endl
        << "Total number of planes refused for landing "
        << num_land_refused << endl
        << "Total number of planes refused for takeoff "
        << num_takeoff_refused << endl
        << "Total number of planes that landed "
        << num_landings << endl
        << "Total number of planes that took off "
        << num_takeoffs << endl
        << "Total number of planes left in landing queue "
        << landing.size() << endl
        << "Total number of planes left in takeoff queue "
        << takeoff_ext.size() << endl
        << "Total number of planes crashed due to empty fuel tank waiting to land "
        << num_crashes << endl;
    cout << "Percentage of time runway idle "
        << 100.0 * ((float)idle_time) / ((float)time) << "%" << endl;
    cout << "Average wait in landing queue "
        << ((float)land_wait) / ((float)num_landings) << " time units";
    cout << endl << "Average wait in takeoff queue "
        << ((float)takeoff_wait) / ((float)num_takeoffs)
        << " time units" << endl;
    cout << "Average observed rate of planes wanting to land "
        << ((float)num_land_requests) / ((float)time)
        << " per time unit" << endl;
    cout << "Average observed rate of planes wanting to take off "
        << ((float)num_takeoff_requests) / ((float)time)
        << " per time unit" << endl;
}


int main()     //  Airport simulation program
/*
Pre:  The user must supply the number of time intervals the simulation is to
      run, the expected number of planes arriving, the expected number
      of planes departing per time interval, and the
      maximum allowed size for runway queues.
Post: The program performs a random simulation of the airport, showing
      the status of the runway at each time interval, and prints out a
      summary of airport operation at the conclusion.
Uses: Classes Runway, Plane, Random and functions run_idle, initialize.
*/

{
    int end_time;            //  time to run simulation
    int queue_limit;         //  size of Runway queues
    int flight_number = 0;
    double arrival_rate, departure_rate;
    initialize(end_time, queue_limit, arrival_rate, departure_rate);
    int fuel_rate = 5;
    Random variable;
    Runway small_airport(queue_limit);

    for (int current_time = 0; current_time < end_time; current_time++) { //  loop over time intervals

        int number_arrivals = variable.poisson(arrival_rate);  //  current arrival requests
        small_airport.CheckPlaneFuel();

        for (int i = 0; i < number_arrivals; i++) {
            int fuel_level = variable.poisson(fuel_rate);
            Plane current_plane(flight_number++, current_time, arriving, fuel_level);
            if (small_airport.can_land(current_plane) != success)
                current_plane.refuse();
        }

        int number_departures = variable.poisson(departure_rate); //  current departure requests

        for (int j = 0; j < number_departures; j++) {
            int fuel_level = variable.poisson(fuel_rate);
            Plane current_plane(flight_number++, current_time, departing, fuel_level);
            if (small_airport.can_depart(current_plane) != success)
                current_plane.refuse();
        }

        Plane moving_plane;
        switch (small_airport.activity(current_time, moving_plane)) {
            //  Let at most one Plane onto the Runway at current_time.
        case land:
            moving_plane.land(current_time);
            break;
        case takeoff_enum:
            moving_plane.fly(current_time);
            break;
        case idle:
            run_idle(current_time);
        }
    }
    small_airport.shut_down(end_time);
}


/*************************************************************************/
