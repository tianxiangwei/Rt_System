#include <iostream>
#include <sstream>
#include <thread>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/sysinfo.h>
#include <chrono>
#include <vector>
#include <sched.h>
#include <unistd.h>

uint32_t set_sched_setaffinity(std::vector<uint32_t>& cpu_id){
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    for (uint32_t i = 0; i < cpu_id.size(); i++){
        CPU_SET(cpu_id[i], &cpuset);
    }
    uint32_t ret = sched_setaffinity(0, sizeof(cpuset), &cpuset);
    if (ret != 0){
        std::cout<< "sched set affinity failed" << std::endl;
    }
    return ret;
}

std::thread thread_array[10];

void frame_func(int i){
    std::stringstream thread_name; 
    thread_name << "frame" << i; 
    prctl(PR_SET_NAME, thread_name.str().c_str());
    
    uint64_t round = 0;
    
    std::vector<uint32_t> cpu_id;
    cpu_id.push_back(i);
    set_sched_setaffinity(cpu_id);


    while (true){
  
      uint64_t count = 10000;
      double total_value = 0.0;
      total_value += 6.6;

      for(uint64_t i = 0; i< count; i++){
          total_value += 6.6;
      }

      std::this_thread::sleep_for(std::chrono::microseconds(1000));

    } 
}

void test_func(int i){
    std::stringstream thread_name; 
    thread_name << "test" << i; 
    prctl(PR_SET_NAME, thread_name.str().c_str());
    
    uint64_t round = 0;
    
    std::vector<uint32_t> cpu_id;
    cpu_id.push_back(i%3);
    set_sched_setaffinity(cpu_id);


   /*double *test1 = (double *)malloc(sizeof(double)); 
   while (true){
        *test1 += 6.6;
    }*/
  
    while (true){
  
      uint64_t count = 1000000000;
      double total_value = 0.0;
      total_value += 6.6;
      continue;
      /*uint64_t before_time = std::chrono::duration_cast<std::chrono::milliseconds>
          (std::chrono::system_clock::now().time_since_epoch()).count();*/

      for(uint64_t i = 0; i< count; i++){
          total_value += 6.6;
      } 

      /*uint64_t after_time = std::chrono::duration_cast<std::chrono::milliseconds>
          (std::chrono::system_clock::now().time_since_epoch()).count();*/
      
      //std::cout << thread_name.str() << " round " << round << " cost time " << after_time - before_time << std::endl;
      round++;
      //sleep(3);
      
    }

}

int main()
{
    std::vector<uint32_t> cpu_id;
    cpu_id.push_back(0);
    set_sched_setaffinity(cpu_id);

    sleep(20);
    
    /*for (int i = 0; i< 2 ; i++){
        thread_array[i] = std::thread(frame_func, i);       
    }*/
    
    //固定cpu上跑一个任务耗时x,cpu跑满，将三个任务同时放在cpu上耗时为3x, 其中每个任务的cpu消耗为33%
    for (int i = 2; i< 12 ; i++){
        thread_array[i] = std::thread(test_func, i);       
    }

    getchar();
    return 0;

}
