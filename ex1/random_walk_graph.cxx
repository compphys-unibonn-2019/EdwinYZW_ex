#include <vector>
#include <math.h>
#include "TRandom3.h"
#include "TLatex.h"
void random_walk_graph(){
    auto rand_ger = new TRandom3(0);
    auto canvas = new TCanvas("c","c", 1500,600);
    int max_step = 10000;
    int min_step = 1000;
    int div = 50;
    auto graph = new TGraphErrors((int)(max_step-min_step)/div+1);
    graph->SetMarkerColor(4);
    graph->SetMarkerStyle(21);
    
    const int rep = 100;
    vector<double> d;
    int i_data = 0;
    canvas->Draw();
    for(int step = min_step; step < max_step+1; step += div)
    {   
        d.clear();
        for (int i_rep = 0; i_rep < rep; i_rep++)
        {
            int x = 0;
            int y = 0;
            int rand = 0;
            for (int i = 1; i < step; i++)
            {
                rand = rand_ger->Integer(4);
                switch (rand)
                {
                case 0:
                    x += 1;
                    y += 0;
                    break; // right
                case 1:
                    x += 0;
                    y += -1;
                    break; // down
                case 2:
                    x += -1;
                    y += 0;
                    break; // left
                case 3:
                    x += 0;
                    y += +1;
                    break; // up
                }
            }
            d.push_back(sqrt(x * x + y * y));
            //cout <<"x: " << x << " y: " << y  << " d: "<< d[i_rep] << endl;
        }
        graph->SetPoint(i_data, sqrt(step), TMath::Mean(d.begin(), d.end()));
        graph->SetPointError(i_data, 0, TMath::RMS(d.begin(), d.end()));
        i_data++;
    }
    graph->Draw("AP");
    graph->GetXaxis()->SetTitle("#sqrt{N}");
    graph->GetYaxis()->SetTitle("#LT R #GT");
    auto fun = new TF1("fun","[0]*x+[1]",min_step, max_step);
    graph->Fit("fun");
    std::ostringstream function;
    function <<"#it{y} =" <<setprecision(2)<< fun->GetParameter(0) <<" #it{x} " << showpos<< fixed << setprecision(2)<<fun->GetParameter(1);

    auto legend = new TLegend(0.1,0.8,0.3, 0.9);
    legend->AddEntry(graph, "#LT R #GT", "ep");
    legend -> AddEntry (fun, function.str().c_str());
    legend -> Draw();

    canvas->SaveAs("distribution.pdf");
}