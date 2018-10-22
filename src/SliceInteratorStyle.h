#ifndef SLICEINTERATORSTYLE_H
#define SLICEINTERATORSTYLE_H


#include <vtkSmartPointer.h>
#include <vtkObjectFactory.h>
// headers needed for this example
#include <vtkImageViewer2.h>
#include <vtkInteractorStyleImage.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include "ImageViewer.h"

class ImageViewer;

// Define own interaction style
class SliceInteratorStyle : public vtkInteractorStyleImage
{

protected:
   vtkImageViewer2* _ImageViewer;
   int _Slice;
   int _MinSlice;
   int _MaxSlice;
   ImageViewer *viewer_;

public:
   void SetImageViewer(vtkImageViewer2* imageViewer, ImageViewer *viewer = nullptr) {
      _ImageViewer = imageViewer;
      _MinSlice = imageViewer->GetSliceMin();
      _MaxSlice = imageViewer->GetSliceMax();
      _Slice = _MinSlice;
      viewer_ = viewer;
   }

   void SetCurrentSlice(int slice){
       _Slice = slice;
       _ImageViewer->SetSlice(slice);
   }


protected:
   void MoveSliceForward() {
      if(_Slice < _MaxSlice) {
         _Slice += 1;
         _ImageViewer->SetSlice(_Slice);
         _ImageViewer->Render();
         viewer_->GetInfo().current_slice_ = _Slice;
         viewer_->SetInfo();
      }
   }

   void MoveSliceBackward() {
      if(_Slice > _MinSlice) {
         _Slice -= 1;
         _ImageViewer->SetSlice(_Slice);
         _ImageViewer->Render();
         viewer_->GetInfo().current_slice_ = _Slice;
         viewer_->SetInfo();
      }
   }


   virtual void OnKeyDown() {
      std::string key = this->GetInteractor()->GetKeySym();
      if(key.compare("Up") == 0) {
         //cout << "Up arrow key was pressed." << endl;
         MoveSliceForward();
      }
      else if(key.compare("Down") == 0) {
         //cout << "Down arrow key was pressed." << endl;
         MoveSliceBackward();
      }
      // forward event
      vtkInteractorStyleImage::OnKeyDown();
   }


   virtual void OnMouseWheelForward() {
      //std::cout << "Scrolled mouse wheel forward." << std::endl;
      MoveSliceForward();
      // don't forward events, otherwise the image will be zoomed
      // in case another interactorstyle is used (e.g. trackballstyle, ...)
      // vtkInteractorStyleImage::OnMouseWheelForward();
   }


   virtual void OnMouseWheelBackward() {
      //std::cout << "Scrolled mouse wheel backward." << std::endl;
      if(_Slice > _MinSlice) {
         MoveSliceBackward();
      }
      // don't forward events, otherwise the image will be zoomed
      // in case another interactorstyle is used (e.g. trackballstyle, ...)
      // vtkInteractorStyleImage::OnMouseWheelBackward();
   }
};

#endif // SLICEINTERATORSTYLE_H
