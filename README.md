1) Tiny Multimedia Framework (tmf)
===============================

Tiny Multimedia Framework is a simple multimedia framework to implement multimedia applications. A multimedia application consists of a pipeline and a series of filters connected to each other. An application developer need to know about filter types, and how to connect them to each other.

Each filter has a number of input and output ports. Each port has a buffer type and can be connected to other ports with the same type of data. Filters with same type of ports can be connected to each other. A port put the data on its buffer and all consumers are notified.

In section 5 we explain how a multimedia application developers create an application using the APIs of the framework. In section 6 we explain how plug-in developers create a new filter using APIs of the framework.

2) Folder structure
===================

Here is how the project is organized.

	build (cmake build directory)
	core (core package)
	doc (documentations)
	  design
	    tmf.docx (desing document in docx)
	    tmf.pdf (design document in pdf)
	    tmf.eap (UML diagrams in Enterprise Architect)
	  latex (reference manuals in latex)
	  html (reference manuals in html)
	examples (contains examples using tmf library)
	filters (implementation of the filters)
	tmffactory (implementations of factories used by application developers)
	tools (tools to be used by filter implementors)
	types (implementation of new buffer types)
	LICENCE
	README.md
	tmf.doxyfile

3) Installation
===============
```bash
  cd build
  ./build.sh
  # or
  ./build-debug.sh # for debuging
```
Before compilation make sure that the following libraries are installed:

 - libavformat-dev
 - libavcodec-dev
 - libavutil-dev
 - libswscale-dev
 - libsdl1.2-dev
 - zlib1g-dev

4) Development envirement
======================
Tiny Multimedia Framework is configured to be developed under KDevelop IDE.
	
	kdevelop -p tmf.kdev4
	
The build directory:

	build-kdevelop

5) User manual
===========

To create an application we need to create the pipeline as well as the filters, connect filters to each other and run the pipeline. TMF provides APIs to do it.

Here is a producer/consumer example with one producer and three consumer:
```c++
  TMF tmf;
  
  Pipeline* pipe = tmf.createPipeline("Three consumer/One producer");
  
  Filter* producer = tmf.createFilter(STRINGPRODUCER_FILTER, "producer");

  Filter* consumer1 = tmf.createFilter<string>(CONSUMER_FILTER, "consumer1");
  Filter* consumer2 = tmf.createFilter<string>(CONSUMER_FILTER, "consumer2");
  Filter* consumer3 = tmf.createFilter<string>(CONSUMER_FILTER, "consumer3");
  
  producer->setProp("limit", 10);
  
  pipe->connectFilters(producer, consumer1);
  pipe->connectFilters(producer, consumer2);
  pipe->connectFilters(producer, consumer3);

  pipe->init();
  
  pipe->run();
  
  tmf.destroyPipeline(pipe);
```	

6) Plugin developer manual
=======================

Plug-in developers must implement new filters in filter folder. A filter inherits from the Filter class. Each filter must define a set of ports and their data type. The filter then implements ```init()``` and ```run()``` functions.

Here is an example of a filter implementation:
```c++
template <typename T>
class ConsumerFilter: public Filter {
  
private:
  InputPort<T> * input;
public:
  
  ConsumerFilter(const string & name) : Filter(name) {
    input = new InputPort<T>("input");
    
    inputPorts.push_back(input);
  }
  
  void run() {
    
    input->lock();
    
    T * inputData = input->get();
    
    std::stringstream inputstr;
    inputstr << "consuming " << *inputData;
    
    log(inputstr.str());
    sleep(500);
    
    if (input->getStatus() == SampleStatus::EOS)
      status = FilterStatus::EOS; 
    
    input->unlock();
    
  }
  
  ~ConsumerFilter() {
    delete input;
  }
  
};
```

For more information, examples, and documentation please see ```doc``` and ```examples``` folder.
