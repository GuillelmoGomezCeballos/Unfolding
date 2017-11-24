#! /usr/bin/env python

import sys, os, string, re, time, datetime
from multiprocessing import Process
from array import *
from ROOT import *

#from tdrStyle import *
#setTDRStyle()

#folder = '/afs/cern.ch/user/z/zdemirag/www/zpt/panda/'
folder = './'

for i in range(1,6):

    f1 = TFile("higgsCombineTest.MultiDimFit.mH111"+str(i)+".root","READ")
    h1 = TH2D("h1","h1",1000,0.8,1.2,1000,0,5)
    limit1 = f1.Get("limit")
    limit1.Draw("2*deltaNLL:r_s"+str(i)+">>h1","2*deltaNLL<5","goff")

    f2 = TFile("higgsCombineTest.MultiDimFit.mH112"+str(i)+".root","READ")
    h2 = TH2D("h2","h2",1000,0.8,1.2,1000,0,5)
    limit2 = f2.Get("limit")
    limit2.Draw("2*deltaNLL:r_s"+str(i)+">>h2","2*deltaNLL<5","goff")

    f3 = TFile("higgsCombineTest.MultiDimFit.mH113"+str(i)+".root","READ")
    h3 = TH2D("h3","h3",1000,0.8,1.2,1000,0,5)
    limit3 = f3.Get("limit")
    limit3.Draw("2*deltaNLL:r_s"+str(i)+">>h3","2*deltaNLL<5","goff")

    f4 = TFile("higgsCombineTest.MultiDimFit.mH114"+str(i)+".root","READ")
    h4 = TH2D("h4","h4",1000,0.8,1.2,1000,0,5)
    limit4 = f4.Get("limit")
    limit4.Draw("2*deltaNLL:r_s"+str(i)+">>h4","2*deltaNLL<5","goff")
    
    f5 = TFile("higgsCombineTest.MultiDimFit.mH115"+str(i)+".root","READ")
    h5 = TH2D("h5","h5",1000,0.8,1.2,1000,0,5)
    limit5 = f5.Get("limit")
    limit5.Draw("2*deltaNLL:r_s"+str(i)+">>h5","2*deltaNLL<5","goff")

    f6 = TFile("higgsCombineTest.MultiDimFit.mH1115"+str(i)+".root","READ")
    h6 = TH2D("h6","h6",1000,0.8,1.2,1000,0,5)
    limit6 = f6.Get("limit")
    limit6.Draw("2*deltaNLL:r_s"+str(i)+">>h6","2*deltaNLL<5","goff")

    



    c1 = TCanvas("c1","c1",700,700)
    c1.cd()

    h1.GetXaxis().SetTitle("POI "+str(i))
    h1.GetYaxis().SetTitle("2 * Delta NLL")
    h1.GetYaxis().CenterTitle()
    h1.GetYaxis().SetTitleOffset(1.2)
    h1.GetYaxis().SetRangeUser(0,2)
    h1.GetXaxis().SetRangeUser(0.96,1.04)

    h1.GetXaxis().SetTitleOffset(1.2)

    h1.SetMarkerColor(2)
    h1.SetMarkerStyle(20)
    h1.SetMarkerSize(0.5)
    h1.SetTitle("")
    h1.Draw()
    h2.SetMarkerColor(4)
    h2.SetMarkerStyle(20)
    h2.SetMarkerSize(0.5)
    #h2.GetXaxis().SetRangeUser(0.99, 1.01)
    h2.Draw("same")

    h3.SetMarkerColor(1)
    h3.SetMarkerStyle(20)
    h3.SetMarkerSize(0.5)
    #h3.GetXaxis().SetRangeUser(0.99, 1.01)

    h3.Draw("same")

    h4.SetMarkerColor(3)
    h4.SetMarkerStyle(20)
    h4.SetMarkerSize(0.5)    
    #h4.GetXaxis().SetRangeUser(0.99, 1.01)

    h4.Draw("same")


    h5.SetMarkerColor(6)
    h5.SetMarkerStyle(20)
    h5.SetMarkerSize(0.5)
    h5.Draw("same")
    



    h6.SetMarkerColor(7)
    h6.SetMarkerStyle(20)
    h6.SetMarkerSize(0.5)
    #h6.Draw("same")


    gStyle.SetOptStat(0)

    

    leg = TLegend(.7,.7,.95,.9)
    leg.SetFillStyle(0)     
    leg.SetBorderSize(0) 
    leg.AddEntry(h1   ,"lepeff","p")
    leg.AddEntry(h2   ,"momres","p") 
    leg.AddEntry(h3   ,"pdf","p")
    leg.AddEntry(h4   ,"qcd","p")
    leg.AddEntry(h5   ,"lumi","p")
    leg.AddEntry(h6   ,"lep+lumi","p")
    leg.Draw()

    c1.SaveAs(folder+"/poi_"+str(i)+".pdf")
#c1.SaveAs(folder+"/poi_"+str(i)+".png")
    c1.SaveAs(folder+"/poi_"+str(i)+".C")

   # del c1,f1,limit1,f2,limit2,h2,h1
