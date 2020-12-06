#include "script_runner.h"
#include "ros_parameter.hpp"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


ScriptRunner::ScriptRunner(const ros::NodeHandle& nh, const ros::NodeHandle& private_nh)
: _nh(nh)
{   
    LoadParam(private_nh, "script_path", _script_path); 

    std::string script_service = "run_script"; 
    _script_svr = _nh.advertiseService(script_service, &ScriptRunner::ScriptService, this);
    ROS_INFO_STREAM("Advertised script service: " << script_service); 
}

// shell command service 
bool ScriptRunner::ScriptService(shell_runner::RunScript::Request &request,
                                 shell_runner::RunScript::Response &response)
{
    std::string script = request.script;
    std::string args = request.args;  
    ROS_INFO_STREAM("script service request: " << script << " " << args);

    if (script.empty())
    {
        ROS_WARN_STREAM("No script in request!"); 
        response.success = false;  
        response.message = "No script in request!"; 
        return false;
    }

    std::string script_file;
    script_file = _script_path.empty() ? "./" + script : _script_path + "/" + script; 
    if (!fs::exists(script_file)) 
    {
        ROS_WARN_STREAM("Script file not found: " << script_file); 
        response.success = false;  
        response.message = "Script file not found!"; 
        return false;
    }

    std::string command_line = "bash " + script_file; 
    if (!args.empty()) command_line = command_line + " " + args; 
    ROS_INFO_STREAM("Shell command line: " << command_line);
    system(command_line.c_str());
    response.success = true;  
    return true; 
}
