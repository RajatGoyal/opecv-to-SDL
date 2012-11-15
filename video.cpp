#include <cv.h>    
#include <cxcore.h>      
#include <highgui.h>      
#include "SDL/SDL.h"
#include "SDL/SDL_draw.h"
#include "SDL/SDL_ttf.h"
#include <iostream>

using namespace std;
SDL_Surface *ipl_to_surface (IplImage *opencvimg)
{
    int pitch = opencvimg->nChannels*opencvimg->width;
    printf("Depth %d, nChannels %d, pitch %d\n", opencvimg->depth,
                    opencvimg->nChannels, pitch);
SDL_Surface *surface = SDL_CreateRGBSurfaceFrom((void*)opencvimg->imageData,
                opencvimg->width,
                opencvimg->height,
                opencvimg->depth*opencvimg->nChannels,
                opencvimg->widthStep,
                0xff0000, 0x00ff00, 0x0000ff, 0
                );
return surface;

}

int main()  
{        
    int key = 0;  
   
    CvCapture* capture = cvCaptureFromAVI( "/home/rajat/1.mpg" );    
    IplImage* frame = cvQueryFrame( capture );  
  
    // Check   
    if ( !capture )   
    {  
        fprintf( stderr, "Cannot open AVI!\n" );  
        return 1;  
    }  
  
    // Get the fps, needed to set the delay  
    int fps = ( int )cvGetCaptureProperty( capture, CV_CAP_PROP_FPS );  
   
    // Create a window to display the video  
  //  cvNamedWindow( "video", CV_WINDOW_AUTOSIZE );  
  
   SDL_Surface* screen = NULL;
  screen = SDL_SetVideoMode(frame->width,frame->height,24,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_NOFRAME);

   
    SDL_Init( SDL_INIT_EVERYTHING );

    while( key != 'x' )   
    {  
        // get the image frame   
        frame = cvQueryFrame( capture );  
        // exit if unsuccessful  
        if( !frame ) break;  
  	SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 255, 255, 
255, 255));
	SDL_Surface *surf = ipl_to_surface(frame);
	SDL_BlitSurface(surf, NULL, screen, NULL);
	SDL_FreeSurface(surf);
	SDL_Flip(screen);      // display current frame   
        //cvShowImage( "video", frame );  
        // exit if user presses 'x'          
        key = cvWaitKey( 1000 / fps );  
    }  
   
    // Tidy up  
    cvDestroyWindow( "video" );  
    cvReleaseCapture( &capture );  
  
    return 0;  
} 
