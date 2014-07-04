//ServerQrobot.cpp

#include "ServerCamera.h"

#include <thread>

using namespace std;

/*void waiting()
{
	char temp;
	cin >> temp;
	if(temp == 'q')
	{
		ServerCamera::flag = true;
	}
}*/


//bool ServerCamera::flag = false;

ServerCamera::ServerCamera()
{
	name = "ServerCamera";


	myInput = new InputServerCameraMessage;
	myOutput = new OutputServerCameraMessage;

	inputMessage = myInput;
	outputMessage = myOutput;

  

	myRegister();
}

ServerCamera::~ServerCamera()
{
	delete myInput;
	delete myOutput;
}

size_t ServerCamera::getInputMessageSize()
{
	return sizeof(InputServerCameraMessage);
}

size_t ServerCamera::getOutputMessageSize()
{
	return sizeof(OutputServerCameraMessage);
}

void ServerCamera::work()
{
  CommandType command = myInput->commandName;
	
	int *result = new int[2];
	result[0] = result[1] = -1;
	switch(command)
	{
		case getcamera:
		  result[0] = get_camera(); 
     			 break;
		case getpicture:
		  result[0] = get_picture();
			break;
		case movedetect:
		  result[0] = move_detect();
			break;
		case cutimage:
		  result[0] = cut_image(myInput->parameters);
			break;
		
    default:
		  break;
	}
  myOutput->returnValues[0] = result[0];
  myOutput->returnValues[1] = result[1];
	cout << myOutput->returnValues[0] << '\t' << myOutput->returnValues[1] << endl;
	delete result;
}

bool ServerCamera::get_camera()  
{   time_t begin;
    time(&begin);
    CvCapture* pCap = cvCreateCameraCapture( -1 );
    IplImage *frame = NULL;  
  
    if (cvCreateCameraCapture == NULL)  
    {  
        return (0);
    }  
  
    cvNamedWindow("Camera",CV_WINDOW_FULLSCREEN);  

    //thread t1(waiting);
    //t1.join();
    //cout << "thread" << endl;
  
 while ((frame = cvQueryFrame(pCap)) != 0 )    
    {  
        time_t now;
        time(&now);
	cout << "while" << endl;
        frame = cvQueryFrame(pCap);  
        cvShowImage("Camera", frame); 


	if(now-begin=20)//close after20s
	break;
        
    }  
  
    cvReleaseCapture(&pCap);    
    cvDestroyWindow("Camera"); 
      return (1);   
    
}  

bool ServerCamera::get_picture()  
{  
    CvCapture* pCap = cvCreateCameraCapture( -1 );   
                                                 //OpenCV会默认调用该摄像头，而不调用系统的驱动   
    IplImage *frame = NULL;  
    char fileName[100];
    char key; 
    int count=0;
  
    if (cvCreateCameraCapture == NULL)  
    {  
        return (0); 
    }  
  
    cvNamedWindow("Camera",CV_WINDOW_FULLSCREEN);  
    
    while (1)    
    {   CvPoint pt1={200,200};
	CvPoint pt2={400,250};
        frame = cvQueryFrame(pCap);
        cvRectangle(frame,pt1,pt2,CV_RGB(0,255,0), 3, 4, 0);  
        cvShowImage("Camera", frame); 
	key=cvWaitKey(20);
	if(key==27)break;	
	if (key==' ')
	{       CvRect rc=cvRect(pt1.x,pt1.y,200,50);
		cvSetImageROI(frame, rc);
		
		IplImage *img_gray=cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
		IplImage *img_binary=cvCreateImage( cvGetSize(frame), IPL_DEPTH_8U, 1 );
		cvCvtColor(frame,img_gray,CV_BGR2GRAY);  
		cvThreshold(img_gray,img_binary,120,255,CV_THRESH_BINARY); 
		sprintf(fileName,"Image %d.jpg",++count);
		cvSaveImage(fileName,frame);
		cvXorS(frame,cvScalarAll(255),frame);
		cvShowImage("Camera",img_binary);
 		cvWaitKey(200); 
	
	} 
	
       
    }  
        
    cvReleaseCapture(&pCap); 
     
    cvDestroyWindow("Camera");    
     return (1);
}
 
bool ServerCamera::move_detect()  
{  
    CvCapture* pCap = cvCreateCameraCapture( -1 );
    IplImage *frame = NULL;  
	char key;
	int count=0;
  
    if (cvCreateCameraCapture == NULL)  
    {  
       return (0);
    }  
  
    cvNamedWindow("Camera",CV_WINDOW_FULLSCREEN);  
    
    while (1)    
    {   CvPoint pt1={200,200};
	CvPoint pt2={400,250};
        frame = cvQueryFrame(pCap);
	CvHaarClassifierCascade * pCascade = 0;  // the face detector  
    CvMemStorage * pStorage = 0;        // expandable memory buffer  
    CvSeq * pFaceRectSeq;               // list of detected faces  
    int i;  
  
    // initializations  
    
    pStorage = cvCreateMemStorage(0);  
    pCascade = (CvHaarClassifierCascade *)cvLoad(("/home/becky/OpenCV-2.4.3/data/haarcascades/haarcascade_frontalface_alt.xml"), 0, 0, 0 );  
  
  
    // validate that everything initialized properly  
    if( !frame || !pStorage || !pCascade ){  
        printf("Initialization failed: %s \n",  
            (!frame)?  "didn't load image file" :  
            (!pCascade)? "didn't load Haar cascade -- "  
                "make sure path is correct" :  
            "failed to allocate memory for data storage");  
        exit(-1);  
    }  
  
    // detect faces in image  
    pFaceRectSeq = cvHaarDetectObjects  
        (frame, pCascade, pStorage,  
        1.1,                       // increase search scale by 10% each pass     
        3,                         // drop groups of fewer than three detections     
        CV_HAAR_DO_CANNY_PRUNING,  // skip regions unlikely to contain a face     
        cvSize(0,0));              // use XML default for smallest search scale  
  
    // draw a rectangular outline around each detection  
    for(i=0;i<(pFaceRectSeq? pFaceRectSeq->total:0); i++ ){  
        CvRect * r = (CvRect*)cvGetSeqElem(pFaceRectSeq, i);  
        CvPoint pt1 = { r->x, r->y };  
        CvPoint pt2 = { r->x + r->width, r->y + r->height };  
        cvRectangle(frame, pt1, pt2, CV_RGB(0,255,0), 3, 4, 0);  
    }  
  
          
        cvShowImage("Camera", frame); 
	key=cvWaitKey(20);
	if(key==27)break;	
	
 
    }  
    cvReleaseImage(&frame); 
    cvReleaseCapture(&pCap);    
    cvDestroyWindow("Camera");    
    return (1);  
} 

bool ServerCamera::cut_image( char* image)
{   
    IplImage* imgSrc = cvLoadImage(image,CV_LOAD_IMAGE_COLOR);
    
    CvHaarClassifierCascade * pCascade = 0;  // the face detector  
    CvMemStorage * pStorage = 0;        // expandable memory buffer  
    CvSeq * pFaceRectSeq;               // list of detected faces  
    int i;  
  
    // initializations  
     
    pStorage = cvCreateMemStorage(0);  
    pCascade = (CvHaarClassifierCascade *)cvLoad  
        (("/home/becky/OpenCV-2.4.3/data/haarcascades/haarcascade_frontalface_alt.xml"), 0, 0, 0 );  
  
  
    // validate that everything initialized properly  
    if( !imgSrc || !pStorage || !pCascade ){  
        printf("Initialization failed: %s \n",  
            (!imgSrc)?  "didn't load image file" :  
            (!pCascade)? "didn't load Haar cascade -- "  
                "make sure path is correct" :  
            "failed to allocate memory for data storage");  
        exit(-1);  
    }  
  
    // detect faces in image  
    pFaceRectSeq = cvHaarDetectObjects  
        (imgSrc, pCascade, pStorage,  
        1.1,                       // increase search scale by 10% each pass     
        3,                         // drop groups of fewer than three detections     
        CV_HAAR_DO_CANNY_PRUNING,  // skip regions unlikely to contain a face     
        cvSize(0,0));              // use XML default for smallest search scale  
  
    // create a window to display detected faces  
    //cvNamedWindow("Haar Window", CV_WINDOW_AUTOSIZE);
    //cvNamedWindow("Window", CV_WINDOW_AUTOSIZE);  
    cvNamedWindow("resize", CV_WINDOW_AUTOSIZE);   
    //draw a same scale picture
	    IplImage *resizeRes;  
            CvSize dst_cvsize;  
            dst_cvsize.width=0.25*imgSrc->width;  
            dst_cvsize.height=0.25*imgSrc->height; 
           
            resizeRes=cvCreateImage(dst_cvsize,imgSrc->depth,imgSrc->nChannels); 
	    
            
    // draw a rectangular outline around each detection  
    for(i=0;i<(pFaceRectSeq? pFaceRectSeq->total:0); i++ ){  
        CvRect * r = (CvRect*)cvGetSeqElem(pFaceRectSeq, i);  
        CvPoint  pt1 = { r->x, r->y };  
        CvPoint  pt2 = { r->x + r->width, r->y + r->height };  
        cvRectangle(imgSrc, pt1, pt2, CV_RGB(0,255,0), 3, 4, 0);
	//cvShowImage("Window", imgSrc);

        CvRect rc_scale = cvRect(pt1.x,pt1.y,r->width*5.5,r->height*3);
	cvSetImageROI(imgSrc, rc_scale);
	cvResize(imgSrc,resizeRes,CV_INTER_CUBIC); 
	 
     //binary the number
	IplImage *img_gray=cvCreateImage( cvGetSize(resizeRes), IPL_DEPTH_8U, 1 );
	IplImage *img_binary=cvCreateImage( cvGetSize(resizeRes), IPL_DEPTH_8U, 1 );
	cvCvtColor(resizeRes,img_gray,CV_BGR2GRAY);  
	cvThreshold(img_gray,img_binary,120,255,CV_THRESH_BINARY); 
            
    //find the number
        CvRect rc_number = cvRect(180,190,150,35);
        
        cvSetImageROI(img_binary, rc_number);
        //cvShowImage( "resize", img_binary ); 
   //surround the number
   IplImage *img_temp=cvCreateImage( cvGetSize(img_binary), IPL_DEPTH_8U, 1 );
    
    CvSeq *first_contour = NULL, *c = NULL; 
    CvMemStorage* mem_storage = cvCreateMemStorage(0);  
    cvFindContours(img_binary, mem_storage, &first_contour, sizeof(CvContour),CV_RETR_LIST ,CV_CHAIN_APPROX_SIMPLE );      
    cvZero(img_temp);      
         
 char filename[100]; 
    int cnt=0;
         for(;first_contour!=0;first_contour=first_contour->h_next)
	{   
            cnt++;
 	    cvDrawContours(img_temp,  first_contour, cvScalar(100), cvScalar(100), 1 ); 
	    CvRect rect = cvBoundingRect(first_contour,0);
		if(rect.height<130&&rect.width>3)  
            {   CvSize size,dst_size;      
                cvRectangle(img_temp, cvPoint(rect.x, rect.y), cvPoint(rect.x + rect.width, rect.y + rect.height),CV_RGB(255,255, 255), 1, 8, 0);
		IplImage *result;
		 size.width=rect.width;
		 size.height=rect.height;
		 result=cvCreateImage( size, img_temp->depth, img_temp->nChannels );
		 //从图像中提取子图像
		 cvSetImageROI(img_temp,rect);
		 cvCopy(img_temp,result);
		 cvResetImageROI(img_temp);
		cvShowImage("resize", img_temp); 
		sprintf(filename,"Image%d.jpg",++cnt);
		dst_size.width=32;
   		dst_size.height=32;
		IplImage* file=0;
		
   		
   		file=cvCreateImage( dst_size, img_temp->depth, img_temp->nChannels );
		cvResize(result, file, CV_INTER_LINEAR); //缩放源图像到目标图像
		cvSaveImage(filename,file);
            }

	}

 
  
   // cvShowImage("Haar Window", imgSrc);  
    cvWaitKey(0);  
    //cvDestroyWindow("Haar Window");  
    //cvDestroyWindow("Window");
    cvDestroyWindow("resize");
	    // clean up and release resources  
    cvReleaseImage(&imgSrc); 
    cvReleaseImage(&resizeRes);
cvReleaseImage(&img_binary);
cvReleaseImage(&img_temp);
//cvReleaseImage(&file); 
   // cvReleaseImage(&imgSrc2);
    
    if(pCascade) cvReleaseHaarClassifierCascade(&pCascade);  
    if(pStorage) cvReleaseMemStorage(&pStorage); } 
    return (1);
                                                                                                                                     
}
  
