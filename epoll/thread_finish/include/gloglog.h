#ifndef GLOGLOG_H
#define GLOGLOG_H

#include <glog/logging.h>
#include "dylibapi.h"

#include <iostream>

using namespace std;

class MyGlogLog
{
public:
    MyGlogLog(string glog_name, string glog_leve, string glog_path)
        :   glog_name_(glog_name),
            glog_leve_(glog_leve),
            glog_path_(glog_path)
    {
        LoadDLL((char *)"libglog.so.0");
        InitGloglog();
    }

    virtual ~MyGlogLog()
    {

    }

    void InitGloglog()
    {
        // Init glog
        google::InitGoogleLogging(glog_name_.c_str());

        // INFO WARNING ERROR FATAL
        if (glog_leve_ == "INFO") {
            FLAGS_stderrthreshold = google::GLOG_INFO;
        } else if (glog_leve_ == "WARNING") {
            FLAGS_stderrthreshold = google::GLOG_WARNING;
        } else if (glog_leve_ == "ERROR") {
            FLAGS_stderrthreshold = google::GLOG_ERROR;
        } else if (glog_leve_ == "FATAL") {
            FLAGS_stderrthreshold = google::GLOG_FATAL;
        }

        FLAGS_log_dir = glog_path_;
        FLAGS_logbufsecs = 0;   // Print log in real time.
        FLAGS_max_log_size = 6; // Max log size 6MB.
        FLAGS_colorlogtostderr = true;

    }

private:
    string glog_name_;
    string glog_leve_;
    string glog_path_;

};

#endif // GLOGLOG_H