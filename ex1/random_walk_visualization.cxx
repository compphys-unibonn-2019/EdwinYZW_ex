#include<vector>
#include "TCanvas.h"
#include "TGraph.h"
#include "TRadom.h"

void random_walk_visualization(){
    auto canvas = new TCanvas("c","c",600,600);
    auto graph = new TGraph(1);
    int loop = 1000;
    vector<TLine*> lines(loop, nullptr);
    lines[0] = new TLine(0,0,0,0);

    graph->SetPoint(0,0,0);
    canvas -> SetGrid();
    canvas -> Draw();
    graph->GetYaxis()->SetRangeUser(-10,10);
    graph->GetXaxis()->SetLimits(-10,10);
    graph->SetMarkerStyle(8);
    graph->SetMarkerColor(2);
    graph->Draw("AP");
    lines[0]->Draw();
    lines[0]->SetLineColor(kRed);

    int x = 0;
    int y = 0;
    int rand = 0;
    int rang = 10;

    for(int i=1; i<loop; i++){
        rand = gRandom->Integer(4);
        switch(rand){
            case 0:x+=1; y+=0; break; // right
            case 1:x+=0; y+=-1; break; // down
            case 2:x+=-1; y+=0; break; // left
            case 3:x+=0; y+=+1; break; // up
        }
        lines[i] = new TLine(lines[i-1]->GetX2(),lines[i-1]->GetY2(),x,y);
        lines[i]->SetLineColor(kRed);
        lines[i]->Draw("SAME");
        graph->SetPoint(0,x,y);
        if(rang < TMath::Abs(x) || rang <TMath::Abs(y)){
            rang+=10;
        }
        graph->GetYaxis()->SetRangeUser(-rang,rang);
        graph->GetXaxis()->SetLimits(-rang,rang);
        canvas->Update();

        gSystem->Sleep(10);
    }
}