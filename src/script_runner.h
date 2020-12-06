#ifndef __SCRIPT_RUNNER_H
#define __SCRIPT_RUNNER_H

#include <ros/ros.h>
#include <shell_runner/RunScript.h>

class ScriptRunner 
{
public: 
    ScriptRunner(const ros::NodeHandle& nh = ros::NodeHandle(), 
                 const ros::NodeHandle& private_nh = ros::NodeHandle("~"));

private: 
    // run script service 
    bool ScriptService(shell_runner::RunScript::Request &request,
                       shell_runner::RunScript::Response &response);

private: 
    ros::NodeHandle _nh;

    // shell script server 
    ros::ServiceServer _script_svr;

    // path for script 
    std::string _script_path; 
};

#endif // ifndef __SCRIPT_RUNNER_H
