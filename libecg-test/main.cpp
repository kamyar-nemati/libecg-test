/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: kamyar
 * Email: <u>kamyarnemati at gmail.com</u>
 *
 * Created on 18 February 2017, 19:16
 * C++ 14
 */

#include <string>

/* libecg */
#include "../libecg/libecg/encoder.h" //Include the Encoder class
#include "../libecg/libecg/decoder.h" //Include the Decoder class

/* © 2015 Advanced Software Engineering Limited. All rights reserved */
#include "ChartDirector/include/chartdir.h"

#include "ScatterPoints.h"

using namespace libecg;

/**
 * @description This function draws a line chart of overlapping signals.
 * 
 * @param <i>const int&</i> <b>dataset_frequency</b> Sample-frequency of 
 * the dataset.
 * @param <i>const int&</i> <b>dataset_length</b> Number of samples in 
 * the dataset.
 * @param <i>const std::string&</i> <b>dataset</b> The path to the dataset.
 * @param <i>const std::string&</i> <b>fileName</b> The file to be created 
 * as the output.
 * @param <i>const int&</i> <b>threshold</b> The threshold size.
 * @param <i>const int&</i> <b>aperture</b> The aperture size.
 * @param <i>const std::list:int* const</i> <b>lst_org</b> List of the 
 * original samples (The original signal).
 * @param <i>const std::list:int* const</i> <b>lst_rec</b> List of the 
 * reconstructed samples (The reconstructed signal).
 * 
 * @return void
 * 
 * @copyright © 2015 Advanced Software Engineering Limited. All rights reserved
 * @adopted_from <a>http://www.advsofteng.com/doc/cdcpp.htm#multiline.htm</a>
 */
void plot_lineChart(
        const int& dataset_frequency, 
        const int& dataset_length, 
        const std::string& dataset, 
        const std::string& fileName, 
        const int& threshold, 
        const int& aperture, 
        const std::list<int>* const lst_org, 
        const std::list<int>* const lst_rec
);

/**
 * @description This function draws a bar chart that represents the overall 
 * compression performance of each and every individual compression that 
 * issued according to the given threshold and aperture.
 * 
 * @param <i>const int&</i> <b>rawResult_length</b> The total number of 
 * compression applied.
 * @param <i>const std::string&</i> <b>dataset</b> The path to the dataset.
 * @param <i>const std::string&</i> <b>fileName</b> The file to be created 
 * as the output.
 * @param <i>const std::list:int* const</i> <b>lst_threshold</b> The threshold 
 * size for each and every individual compression.
 * @param <i>const std::list:int* const</i> <b>lst_aperture</b> The aperture 
 * size for each and every individual compression.
 * @param <i>const std::list:float* const</i> <b>lst_cr</b> The resulting 
 * Compression Ratio for each and every individual compression.
 * @param <i>const std::list:float* const</i> <b>lst_prd</b> The resulting 
 * Percent Root-Mean-Square Difference for each and every individual 
 * compression.
 * @param <i>const std::list:float* const</i> <b>lst_qs</b> The resulting 
 * Quality Score for each and every individual compression.
 * 
 * @return void
 * 
 * @copyright © 2015 Advanced Software Engineering Limited. All rights reserved
 * @adopted_from: <a>http://www.advsofteng.com/doc/cdcpp.htm#multibar.htm</a>
 */
void plot_barChart(
        const int& rawResult_length, 
        const std::string& dataset, 
        const std::string& fileName, 
        const std::list<int>* const lst_threshold, 
        const std::list<int>* const lst_aperture, 
        const std::list<float>* const lst_cr, 
        const std::list<float>* const lst_prd, 
        const std::list<float>* const lst_qs
);

void plot_scatterChart(
        std::list<ScatterPoints*>* lst_scatterPoints, 
        int dataLineColor, 
        std::string xAxisTitle, 
        std::string yAxisTitle, 
        std::string chartTitle, 
        std::string fileName
);

/*
 * 
 */
int main(int argc, char** argv) {
    
    //A prefix for all output files
    const std::string OUTPUT_FILE_PREFIX = "_output_";
    
    //Setting all the output files
    std::string file_com = OUTPUT_FILE_PREFIX + "data_compressed.txt";
    std::string file_rec = OUTPUT_FILE_PREFIX + "data_reconstructed.txt";
    std::string file_ols = OUTPUT_FILE_PREFIX + "plot_overlapping_signals.png";
    std::string file_brs = OUTPUT_FILE_PREFIX + "plot_performance_evaluation.png";
    std::string file_cr_comparison = OUTPUT_FILE_PREFIX + "plot_comparison_cr.png";
    std::string file_prd_comparison = OUTPUT_FILE_PREFIX + "plot_comparison_prd.png";
    std::string file_qs_comparison = OUTPUT_FILE_PREFIX + "plot_comparison_qs.png";
    
    /* -------------------------------------------------------------------------
     * |              Setting variables to initialize compression              |
     * -------------------------------------------------------------------------
     */
    
    //Number of samples that each dataset holds per second.
    int dataset_frequency = 360;
    
    //The dataset file
    /* A short signal */
    int dataset_length = 3600;
    std::string dataset = "ECGs/samples100.txt";
    /* A long signal */
//    int dataset_length = 21600;
//    std::string dataset = "ECGs/samples100_long.txt";
    
    //One compression
    bool to_perform_sample_compression = true;
    int threshold = 7;
    int aperture = 15;
    bool eStat, dStat;
    float cr, prd, qs;
    
    //Multiple Compression
    bool to_perform_evaluation = true;
    int threshold_min = 3;
    int threshold_max = 8;
    int aperture_min = 1;
    int aperture_max = 32;
    
    /* -------------------------------------------------------------------------
     * |                      Perform a sample compression                     |
     * -------------------------------------------------------------------------
     */
    
    if (to_perform_sample_compression) {
        //Create compression object
        Encoder* e = new Encoder(dataset_length, dataset, threshold, aperture, eStat);

        //Is object fine?
        assert(eStat);

        //Compress signal
        assert(e->encode());

        //Write the compressed signal into a file
        assert(e->write(file_com, e->BINARY));

        //Get the compression ratio result
        cr = e->getBinarySequeneCompressionRatio();

        //Print out the compression ratio
        std::printf("CR: %f\n", cr);

        //Create decompression object
        Decoder* d = new Decoder(file_com, Base::BINARY, dStat);

        //Is object fine?
        assert(dStat);

        //Decompress signal
        assert(d->decode());

        //Write the decompressed signal into a file
        assert(d->write(file_rec, d->BINARY));

        //Get the original signal in the form of a list of samples
        std::list<int>* lst_org = new std::list<int>();
        e->getOriginal(lst_org);

        //Get the percent root-mean-square difference result
        prd = d->getPercentRootMeanSquareDifference(lst_org);

        //Print out the percent root-mean-square difference
        std::printf("PRD: %f\n", prd);

        //Calculate the quality score
        qs = cr / prd;

        //Print out the quality score
        std::printf("QS: %f\n", qs);

        //Get the reconstructed signal in the form of a list of samples
        std::list<int>* lst_rec = new std::list<int>();
        d->getReconstructed(lst_rec);

        //Draw a line chart of overlapping signals
        plot_lineChart(dataset_frequency, dataset_length, dataset, file_ols, threshold, aperture, lst_org, lst_rec);

        //Clean up memory
        delete lst_rec;
        delete lst_org;
        delete d;
        delete e;
    }
    
    /* -------------------------------------------------------------------------
     * |Perform a comprehensive performance evaluation on multiple compressions|
     * -------------------------------------------------------------------------
     */
    
    if (to_perform_evaluation) {
        std::list<int>* lst_threshold = new std::list<int>();
        std::list<int>* lst_aperture = new std::list<int>();
        std::list<float>* lst_cr = new std::list<float>();
        std::list<float>* lst_prd = new std::list<float>();
        std::list<float>* lst_qs = new std::list<float>();
        int rawResult_length = 0;
        
        //Scatter plot data
        std::list<ScatterPoints*>* lst_scatterPoints_cr = new std::list<ScatterPoints*>();
        std::list<ScatterPoints*>* lst_scatterPoints_prd = new std::list<ScatterPoints*>();
        std::list<ScatterPoints*>* lst_scatterPoints_qs = new std::list<ScatterPoints*>();
        
        //Start the compression sequence
        for (int i = threshold_min; i < threshold_max; ++i) {
            
            //Create points objects for scatter plot for every threshold value
            ScatterPoints* scatterPoints_cr = new ScatterPoints(i, "Threshold:" + std::to_string(i));
            ScatterPoints* scatterPoints_prd = new ScatterPoints(i, "Threshold:" + std::to_string(i));
            ScatterPoints* scatterPoints_qs = new ScatterPoints(i, "Threshold:" + std::to_string(i));
            
            //Compress using different aperture
            for (int j = aperture_min; j < aperture_max; ++j) {
                lst_threshold->push_back(i);
                lst_aperture->push_back(j);
                Encoder* en = new Encoder(dataset_length, dataset, i, j, eStat);
                assert(eStat);
                assert(en->encode());
                cr = en->getBinarySequeneCompressionRatio();
                lst_cr->push_back(cr);
                std::printf("CR: %f\n", cr);
                Decoder* de = new Decoder(en->getBinarySequeneCompressed(), dStat);
                assert(dStat);
                assert(de->decode());
                std::list<int>* lst_org = new std::list<int>();
                en->getOriginal(lst_org);
                prd = de->getPercentRootMeanSquareDifference(lst_org);
                lst_prd->push_back(prd);
                std::printf("PRD: %f\n", prd);
                qs = cr / prd;
                lst_qs->push_back(qs);
                std::printf("QS: %f\n", qs);
                delete lst_org;
                delete de;
                delete en;
                ++rawResult_length;
                
                //Save points for every aperture value
                scatterPoints_cr->addPoint((double)j, (double)cr);
                scatterPoints_prd->addPoint((double)j, (double)prd);
                scatterPoints_qs->addPoint((double)j, (double)qs);
            }
            
            //Save points objects for every threshold value
            lst_scatterPoints_cr->push_back(scatterPoints_cr);
            lst_scatterPoints_prd->push_back(scatterPoints_prd);
            lst_scatterPoints_qs->push_back(scatterPoints_qs);
        }
        plot_barChart(rawResult_length, dataset, file_brs, lst_threshold, lst_aperture, lst_cr, lst_prd, lst_qs);
        
        //Draw scatter plot
        plot_scatterChart(lst_scatterPoints_cr, 0x99bb55, "Aperture", "Compression Ratio (CR)", "Compression Performance by Threshold", file_cr_comparison);
        plot_scatterChart(lst_scatterPoints_prd, 0xee9944, "Aperture", "Percent Root-Mean-Square Difference (PRD)", "Compression Distortion by Threshold", file_prd_comparison);
        plot_scatterChart(lst_scatterPoints_qs, 0x5588cc, "Aperture", "Quality Score (QS)", "Compression Quality by Threshold", file_qs_comparison);
        
        //Clean up sequence
        delete lst_qs;
        delete lst_prd;
        delete lst_cr;
        delete lst_aperture;
        delete lst_threshold;
        std::list<ScatterPoints*>::iterator it_sp;
        it_sp = lst_scatterPoints_cr->begin();
        for (int i = 0; i < lst_scatterPoints_cr->size(); ++i) {
            delete *it_sp;
            ++it_sp;
        }
        it_sp = lst_scatterPoints_prd->begin();
        for (int i = 0; i < lst_scatterPoints_prd->size(); ++i) {
            delete *it_sp;
            ++it_sp;
        }
        it_sp = lst_scatterPoints_qs->begin();
        for (int i = 0; i < lst_scatterPoints_qs->size(); ++i) {
            delete *it_sp;
            ++it_sp;
        }
        delete lst_scatterPoints_cr;
        delete lst_scatterPoints_prd;
        delete lst_scatterPoints_qs;
    }
    
    return 0;
}

void plot_lineChart(
        const int& dataset_frequency, 
        const int& dataset_length, 
        const std::string& dataset, 
        const std::string& fileName, 
        const int& threshold, 
        const int& aperture, 
        const std::list<int>* const lst_org, 
        const std::list<int>* const lst_rec
) {
    const int CHART_HEIGHT = 900;
    
    // The data for the line chart
    double data0_org[dataset_length] = {};
    double data1_rec[dataset_length] = {};

    // The labels for the line chart
    char *labels[dataset_length] = {};
    
    /* CUSTOMISED CODE TO INJECT DATASET INTO THE PLOT OBJECT */
    std::list<int>::const_iterator ot = lst_org->begin();
    std::list<int>::const_iterator rt = lst_rec->begin();
    char *label;
    for (int i = 0; i < dataset_length; ++i) {
        data0_org[i] = (double)(*ot);
        data1_rec[i] = (double)(*rt);
        std::string str = std::to_string(i + 1);
        label = new char[str.length() + 1];
        std::strcpy(label, str.c_str());
        labels[i] = label;
        ++ot;
        ++rt;
    }
    /* -END- */

    // Create an XYChart object of size (samples * 2) x CHART_HEIGHT pixels, with a light blue (EEEEFF) background,
    // black border, 1 pixel 3D border effect and rounded corners
    XYChart *c = new XYChart((dataset_length * 2), CHART_HEIGHT, 0xeeeeff, 0x000000, 1);
    c->setRoundedFrame();

    // Set the plotarea at (55, 58) and of size (samples * 2 - 80) x (CHART_HEIGHT - 105) pixels, with white background. Turn on
    // both horizontal and vertical grid lines with light grey color (0xcccccc)
    c->setPlotArea(55, 58, (dataset_length * 2) - 80, CHART_HEIGHT - 105, 0xffffff, -1, -1, 0xcccccc, 0xcccccc);

    // Add a legend box at (50, 30) (top of the chart) with horizontal layout. Use 9pt Arial Bold
    // font. Set the background and border color to Transparent.
    c->addLegend(50, 30, false, "arialbd.ttf", 9)->setBackground(Chart::Transparent);

    // Add a title box to the chart using 15pt Times Bold Italic font, on a light blue (CCCCFF)
    // background with glass effect. white (0xffffff) on a dark red (0x800000) background, with a 1
    // pixel 3D border.
    std::string title = "ECG Signal Data Compression \"" + dataset + "\" (Threshold: " + std::to_string(threshold) + " & Aperture: " + std::to_string(aperture) + ")";
    c->addTitle(title.c_str(), "timesbi.ttf", 15)->setBackground(0xccccff, 0x000000, Chart::glassEffect());

    // Add a title to the y axis
    std::string titleY = "Amplitude / Voltage";
    c->yAxis()->setTitle(titleY.c_str());

    // Set the labels on the x axis.
    c->xAxis()->setLabels(StringArray(labels, (int)(sizeof(labels) / sizeof(labels[0]))));

    // Display 1 out of 25 labels on the x-axis.
    c->xAxis()->setLabelStep(dataset_frequency);

    // Add a title to the x axis
    std::string titleX = "Sample (Frequency: " + std::to_string(dataset_frequency) + "Hz)";
    c->xAxis()->setTitle(titleX.c_str());

    // Add a line layer to the chart
    LineLayer *layer = c->addLineLayer();

    // Set the default line width to 1 pixels
    layer->setLineWidth(1);

    // Add the three data sets to the line layer
    layer->addDataSet(DoubleArray(data0_org, (int)(sizeof(data0_org) / sizeof(data0_org[0]))), 0x0000ff, "Original Signal");
    layer->addDataSet(DoubleArray(data1_rec, (int)(sizeof(data1_rec) / sizeof(data1_rec[0]))), 0xff0000, "Reconstructed Signal");

    // Output the chart
    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    for (int i = 0; i < dataset_length; ++i) {
        delete labels[i];
    }
}

void plot_barChart(
        const int& rawResult_length, 
        const std::string& dataset, 
        const std::string& fileName, 
        const std::list<int>* const lst_threshold, 
        const std::list<int>* const lst_aperture, 
        const std::list<float>* const lst_cr, 
        const std::list<float>* const lst_prd, 
        const std::list<float>* const lst_qs
) {
    const int CHART_HEIGHT = 900;
    
    // The data for the bar chart
    double data0_cr[rawResult_length] = {};
    double data1_prd[rawResult_length] = {};
    double data2_qs[rawResult_length] = {};
    const char *labels[rawResult_length] = {};
    
    /* CUSTOMISED CODE TO INJECT DATASET INTO THE PLOT OBJECT */
    std::list<int>::const_iterator tt = lst_threshold->begin();
    std::list<int>::const_iterator at = lst_aperture->begin();
    std::list<float>::const_iterator ct = lst_cr->begin();
    std::list<float>::const_iterator pt = lst_prd->begin();
    std::list<float>::const_iterator qt = lst_qs->begin();
    char *label;
    for (int i = 0; i < rawResult_length; ++i) {
        data0_cr[i] = (double)(*ct);
        data1_prd[i] = (double)(*pt);
        data2_qs[i] = (double)(*qt);
        std::string str = "T:" + std::to_string(*tt) + "-A:" + std::to_string(*at);
        label = new char[str.length() + 1];
        std::strcpy(label, str.c_str());
        labels[i] = label;
        ++tt;
        ++at;
        ++ct;
        ++pt;
        ++qt;
    }
    /* -END- */

    // Create a XYChart object of size (64px for each column) x CHART_HEIGHT pixels
    XYChart *c = new XYChart((rawResult_length * 64), CHART_HEIGHT);

    // Add a title to the chart using 10 pt Arial font
    std::string title = "ECG Signal Data Compression Performance Evaluation \"" + dataset + "\"";
    c->addTitle(title.c_str(), "", 10);

    // Set the plot area at (50, 25) and of size (columns * 64 - 80) x (CHART_HEIGHT - 80). Use two alternative background colors
    // (0xffffc0 and 0xffffe0)
    c->setPlotArea(50, 25, ((rawResult_length * 64) - 80), CHART_HEIGHT - 80, 0xffffc0, 0xffffe0);

    // Add a legend box at (55, 18) using horizontal layout. Use 8 pt Arial font, with transparent
    // background
    c->addLegend(55, 18, false, "", 8)->setBackground(Chart::Transparent);

    // Add a title to the y-axis
    std::string titleY = "Performance";
    c->yAxis()->setTitle(titleY.c_str());

    // Reserve 20 pixels at the top of the y-axis for the legend box
    c->yAxis()->setTopMargin(20);

    // Set the x axis labels
    c->xAxis()->setLabels(StringArray(labels, (int)(sizeof(labels) / sizeof(labels[0]))));
    
    /* ADD THE X AXIS TITLE */
    std::string titleX = "Compression Performance by Different Threshold and Aperture (T: Threshold, A: Aperture)";
    c->xAxis()->setTitle(titleX.c_str());

    // Add a multi-bar layer with 3 data sets and 3 pixels 3D depth
    BarLayer *layer = c->addBarLayer(Chart::Side, 3);
    layer->addDataSet(DoubleArray(data0_cr, (int)(sizeof(data0_cr) / sizeof(data0_cr[0]))), 0x80ff80, "Compression Ratio (CR)");
    layer->addDataSet(DoubleArray(data1_prd, (int)(sizeof(data1_prd) / sizeof(data1_prd[0]))), 0xff8080, "Percent Root-Mean-Square Difference (PRD)");
    layer->addDataSet(DoubleArray(data2_qs, (int)(sizeof(data2_qs) / sizeof(data2_qs[0]))), 0x8080ff, "Quality Score (QS)");

    // Output the chart
    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
    for (int i = 0; i < rawResult_length; ++i) {
        delete labels[i];
    }
}

void plot_scatterChart(
        std::list<ScatterPoints*>* lst_scatterPoints, 
        int dataLineColor, 
        std::string xAxisTitle, 
        std::string yAxisTitle, 
        std::string chartTitle, 
        std::string fileName
) {
    
    // Create a XYChart object of size 950 x 550 pixels
    XYChart *c = new XYChart(950, 550);

    // Set the plot area at (55, 65) and of size 850 x 430 pixels, with a light grey border
    // (0xc0c0c0). Turn on both horizontal and vertical grid lines with light grey color (0xc0c0c0)
    c->setPlotArea(55, 65, 850, 430, -1, -1, 0xc0c0c0, 0xc0c0c0, -1);

    // Add a legend box at (50, 30) (top of the chart) with horizontal layout. Use 12pt Times Bold
    // Italic font. Set the background and border color to Transparent.
    c->addLegend(50, 30, false, "timesbi.ttf", 12)->setBackground(Chart::Transparent);

    // Add a title to the chart using 18pt Times Bold Itatic font.
    c->addTitle(chartTitle.c_str(), "timesbi.ttf", 18);

    // Add a title to the y axis using 12pt Arial Bold Italic font
    c->yAxis()->setTitle(yAxisTitle.c_str(), "arialbi.ttf", 12);

    // Add a title to the x axis using 12pt Arial Bold Italic font
    c->xAxis()->setTitle(xAxisTitle.c_str(), "arialbi.ttf", 12);

    // Set the axes line width to 3 pixels
    c->xAxis()->setWidth(3);
    c->yAxis()->setWidth(3);

    // The XY points for the scatter chart
    std::list<ScatterPoints*>::iterator it_scatterPoints = lst_scatterPoints->begin();
    for (int i = 0; i < lst_scatterPoints->size(); ++i) {
        double dataX[(*it_scatterPoints)->getCount()] = {};
        double dataY[(*it_scatterPoints)->getCount()] = {};
        
        for (int n = 0; n < (*it_scatterPoints)->getCount(); ++n) {
            (*it_scatterPoints)->getPoint(n, dataX[n], dataY[n]);
        }
        
        int symbol = Chart::NoSymbol;
        switch ((*it_scatterPoints)->getIndex()) {
            case 3:
                symbol = Chart::TriangleSymbol;
                break;
            case 4:
                symbol = Chart::CircleSymbol;
                break;
            case 5:
                symbol = Chart::SquareSymbol;
                break;
            case 6:
                symbol = Chart::DiamondSymbol;
                break;
            case 7:
                symbol = Chart::InvertedTriangleSymbol;
                break;
            default:
                symbol = Chart::CrossSymbol;
                break;
        }
        
        // Add a scatter chart layer, using 10 pixel symbols
        c->addScatterLayer(DoubleArray(dataX, (int)(sizeof(dataX) / sizeof(dataX[0]))), DoubleArray(
            dataY, (int)(sizeof(dataY) / sizeof(dataY[0]))), (*it_scatterPoints)->getName().c_str(),
            symbol, 10, dataLineColor);
        
        ++it_scatterPoints;
    }
    
    // Output the chart
    c->makeChart(fileName.c_str());

    //free up resources
    delete c;
}
