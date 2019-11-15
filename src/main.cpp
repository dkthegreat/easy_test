
#include "easy_log.h"
#include "easy_timer.h"
#include "easy_threadpool.h"
#include "Interpreter.hpp"
#include "MultiThreadModelManager.h"
#include <malloc.h>

using namespace MNN;

void print_tensor(const char * p_name, Tensor * p_tensor)
{
    int n = p_tensor->batch();
    int c = p_tensor->channel();
    int h = p_tensor->height();
    int w = p_tensor->width();
    EASY_LOGI("%s: n = %d, c = %d, h = %d, w = %d\n", p_name, n, c, h, w);
}

class ModelLoader 
{
    typedef struct _handle
    {
        Interpreter * interpreter;
        Session * session;
    }handle_t;
public:
    ModelLoader(const char * p_name) :
    model_name(p_name)
    {

    }

    ~ModelLoader()
    {

    }

    virtual int doJob(MultiThreadModelManager * p_model_manager)
    {
        int ret = 0;
        pthread_t tid = pthread_self();
        //SOFT_ISP_LOGI("doJob tid = %ld", tid);
        handle_t * p_handle = (handle_t*)p_model_manager->GetModel(tid);
        if(p_handle)
        {
            p_handle->interpreter->runSession(p_handle->session);   
        }
        else
        {
            EASY_LOGE("interpreter == NULL");
            exit(-1);
        }

        return ret;
    }

    int loadModel(MultiThreadModelManager * p_model_manager)
    {
        Interpreter * interpreter = Interpreter::createFromFile(model_name);
        ScheduleConfig conf;
        Session* session = interpreter->createSession(conf);
        Tensor * inputTensor = interpreter->getSessionInput(session, NULL);
        //print_tensor("input tensor", inputTensor);

        Tensor * outputTensor = interpreter->getSessionOutput(session, NULL);
        //print_tensor("output tensor", outputTensor);

        pthread_t tid = pthread_self();
        handle_t * p_handle = (handle_t*)malloc(sizeof(handle_t));
        p_handle->interpreter = interpreter;
        p_handle->session = session;
        p_model_manager->AddModel(tid, p_handle);
        
        return (int)(p_handle != NULL);
    }

    int unloadModel(MultiThreadModelManager * p_model_manager)
    {
        pthread_t tid = pthread_self();
        handle_t * p_handle = (handle_t*)p_model_manager->PickModel(tid);
        if(p_handle)
        {
            p_handle->interpreter->releaseSession(p_handle->session);
            delete p_handle->interpreter;
            free(p_handle);
            p_handle = NULL;
        }
        return 0;
    }

private:
    const char * model_name;
};

//
static
void test_squeezenet(int n_thread)
{
    const char * p_model_path = "./squeezenet_v1.1.mnn";
    int n_job_num = 200;
    EasyThreadPool threadpool(n_thread);
    std::vector<std::future<int>> res;
    char timer_name[64];
    sprintf(timer_name, "squeezenet_test: thread %d ", n_thread);
    EasyTimer atm(timer_name);
    ModelLoader model_loader(p_model_path);
    MultiThreadModelManager model_manager;
    //EASY_LOGI("test_squeezenet 1");
    // load model
    for(int i = 0; i < n_thread; i++)
    {
        res.emplace_back(threadpool.enqueue(&ModelLoader::loadModel, &model_loader, &model_manager));
    }
    for(auto && r : res)
    {
        r.get();
    }
    res.clear();
    //EASY_LOGI("test_squeezenet 2");
    // run
    for(int i = 0; i < n_job_num; i++)
    {
        res.emplace_back(threadpool.enqueue(&ModelLoader::doJob, &model_loader, &model_manager));
    }
    for(auto && r : res)
    {
        r.get();
    }
    res.clear();
    //EASY_LOGI("test_squeezenet 3");
    // unload model
    for(int i = 0; i < n_thread; i++)
    {
        res.emplace_back(threadpool.enqueue(&ModelLoader::unloadModel, &model_loader, &model_manager));
    }
    for(auto && r : res)
    {
        r.get();
    }
    res.clear();
    //EASY_LOGI("test_squeezenet out");
}

int main(int argc, char * argv[])
{
    
    int ret = 0;
    //test_squeezenet(8);
#if 1
    test_squeezenet(1);
    test_squeezenet(1);
    test_squeezenet(1);
    test_squeezenet(2);
    test_squeezenet(2);
    test_squeezenet(2);
    test_squeezenet(3);
    test_squeezenet(3);
    test_squeezenet(3);
    test_squeezenet(4);
    test_squeezenet(4);
    test_squeezenet(4);
    test_squeezenet(5);
    test_squeezenet(5);
    test_squeezenet(5);
    test_squeezenet(6);
    test_squeezenet(6);
    test_squeezenet(6);
    test_squeezenet(7);
    test_squeezenet(7);
    test_squeezenet(7);
    test_squeezenet(8);
    test_squeezenet(8);
    test_squeezenet(8);
#endif
    return ret;
}
