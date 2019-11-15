#ifndef _MultiThreadModelManager_H_
#define _MultiThreadModelManager_H_

#include <mutex>
#include <unordered_map>

//
class MultiThreadModelManager
{
public:
    MultiThreadModelManager()
    {

    }

    ~MultiThreadModelManager()
    {

    }

    void AddModel(unsigned long tid, void * p_model)
    {
        std::unique_lock<std::mutex> lock(mutex_map);
        map_tid_pmodel.insert(std::pair<unsigned long, void*>(tid, p_model));
    }

    void * GetModel(unsigned long tid)
    {
        void * p_ret = NULL;
        std::unique_lock<std::mutex> lock(mutex_map);
        auto it = map_tid_pmodel.find(tid);
        if(it != map_tid_pmodel.end())
        {
            p_ret = it->second;
        }
        //SOFT_ISP_LOGI("GetModel p_ret = %p", p_ret);
        return p_ret;
    }

    void * GetModel()
    {
        void * p_ret = NULL;
        std::unique_lock<std::mutex> lock(mutex_map);
        auto it = map_tid_pmodel.begin();
        if(it != map_tid_pmodel.end())
        {
            p_ret = it->second;
        }
        //SOFT_ISP_LOGI("GetModel p_ret = %p", p_ret);
        return p_ret;
    }

    bool HasModel()
    {
        bool bRet = false;
        {
            std::unique_lock<std::mutex> lock(mutex_map);
            if(map_tid_pmodel.size() > 0)
            {
                bRet = true;
            }
        }
        return bRet;
    }

    void * PickModel(unsigned long tid)
    {
        void * p_ret = NULL;
        std::unique_lock<std::mutex> lock(mutex_map);
        auto it = map_tid_pmodel.find(tid);
        if(it != map_tid_pmodel.end())
        {
            p_ret = it->second;
        }
        map_tid_pmodel.erase(it);
        //SOFT_ISP_LOGI("GetModel p_ret = %p", p_ret);
        return p_ret;
    }
    
private:
    std::unordered_map<unsigned long, void*> map_tid_pmodel;
    std::mutex mutex_map;
};

#endif