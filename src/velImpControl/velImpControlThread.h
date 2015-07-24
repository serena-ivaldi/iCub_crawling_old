// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
#ifndef __velImpControlThread__
#define __velImpControlThread__

#include <yarp/os/RateThread.h>
#include <yarp/os/Semaphore.h>
#include <yarp/os/Bottle.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/Vector.h>
#include <yarp/os/ConstString.h>
#include <yarp/os/Time.h>


//class yarp::dev::PolyDriver;

class velImpControlThread: public yarp::os::RateThread
{
private:
    char robotName[255];
    yarp::os:: ConstString limbName;
    yarp::dev::IVelocityControl *ivel;
    yarp::dev::IEncoders        *ienc;
    yarp::dev::IImpedanceControl *iimp;
    yarp::dev::IControlMode *ictrl;
   
    int nJoints;
    yarp::dev::PolyDriver *driver;

    yarp::sig::Vector encoders;
    yarp::sig::Vector encoders_speed;
    yarp::sig::Vector Kp;
    yarp::sig::Vector Kd; //derivative term
    
    yarp::sig::Vector targets;
    yarp::sig::Vector ffVelocities;
    yarp::sig::Vector command;

    yarp::sig::Vector error;
    yarp::sig::Vector error_d;

    yarp::sig::Vector maxVel; //added ludo    
    
    bool suspended;
    int first_command;

    int nb_void_loops;

    yarp::os::Semaphore _mutex;

    int control_rate; //in ms
    
    int state;

    yarp::os::BufferedPort<yarp::os::Bottle> command_port; //deprecated
    yarp::os::BufferedPort<yarp::sig::Vector> command_port2; //new

    double time_watch;
    double time_loop;
    int count;
    double stiff;
    
    FILE *currentSpeedFile;
    FILE *targetSpeedFile;
	FILE *stiffFile;
public:
    velImpControlThread(int rate);
    ~velImpControlThread();

    bool init(yarp::dev::PolyDriver *d, yarp::os::ConstString partName,
              yarp::os::ConstString robotName);
     
    //parameters for impedance control
    int njoints;
    yarp::sig::Vector impContr;
    yarp::sig::Vector contrJoints;	//numbers of joint controlled 
    yarp::sig::Vector swingStiff;	//stiffness for swing 
    yarp::sig::Vector stanceStiff;	//stiffness for stance
    yarp::sig::Vector swingDamp;	//damping
    yarp::sig::Vector stanceDamp;	//damping
    yarp::sig::Vector Grav;			//parameter for gravity compensation 
             
     

    void halt();
    void go();
    void setRef(int i, double pos);

    void setVel(int i, double vel); //added ludovic to set max velocity
    void setGain(int i, double gain); //to set the Kp gains
    void switchImp(double vel); // to switch between different stiffnesses  

    void run();
    bool threadInit();
    void threadRelease();

    void limitSpeed(yarp::sig::Vector &command);
};

#endif

