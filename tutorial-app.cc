/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "tutorial-app.h"
#include "ns3/applications-module.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "ns3/log.h"
using namespace ns3;

TutorialApp::TutorialApp ()
  : m_socket (0),
    m_peer (),
    m_packetSize (0),
    m_nPackets (0),
    m_dataRate (0),
    m_sendEvent (),
    m_running (false),
    m_packetsSent (0)
{
}

TutorialApp::~TutorialApp ()
{
  m_socket = 0;
}

/* static */
TypeId TutorialApp::GetTypeId (void)
{
  static TypeId tid = TypeId ("TutorialApp")
    .SetParent<Application> ()
    .SetGroupName ("Tutorial")
    .AddConstructor<TutorialApp> ()
    ;
  return tid;
}

void
TutorialApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
  m_socket = socket;
  m_peer = address;
  m_packetSize = packetSize;
  m_nPackets = nPackets;
  m_dataRate = dataRate;
}

void
TutorialApp::StartApplication (void)
{
  m_running = true;
  m_packetsSent = 0;
  m_socket->Bind ();
  m_socket->Connect (m_peer);
  //srand(time(NULL));
  SendPacket ();
}

void
TutorialApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void
TutorialApp::SendPacket (void)
{
  Ptr<Packet> packet = Create<Packet> (m_packetSize);
  m_socket->Send (packet);
  //srand((unsigned) time(NULL));
  //uint32_t count = 1;
 // Time tNext = 0; 
  if (++m_packetsSent < m_nPackets)
    {
  //    Ptr<Packet> packet = Create<Packet> (m_packetSize);
  //m_socket->Send (packet);
       //srand((unsigned) time(NULL));
        //double random = rand() ;
       //Time tNext = Seconds( (random/ RAND_MAX) + 1.0) ;
      
      //  NS_LOG_UNCOND ("Generating a packet at time " << Simulator::Now ().GetSeconds ());
      //  NS_LOG_UNCOND ("Packet Sent " << m_packetsSent <<  " " << (tNext + Seconds(m_packetsSent)) << " Random " << (random + 1));


      //srand(time(0));
      //if(m_packetsSent == count){
       // m_sendEvent = Simulator::Schedule (tNext, &TutorialApp::SendPacket, this);
        
      //}
      //count +=1;
           // srand(time(0));

      //m_packetsSent++; 
      ScheduleTx ();
    }
}

void
TutorialApp::ScheduleTx (void)
{
  if (m_running)
    {
//      srand(time(0));


      double temp = 1/ static_cast<double> (m_dataRate.GetBitRate());
      double random_number = ((double)rand()) / RAND_MAX;

      double interval =  - temp * std::log(random_number);
      Time tNext (Seconds (interval));
      //Time tNext(Seconds(temp));
     // NS_LOG_UNCOND ("Generating a packet at  1/interval " << interval);

      m_sendEvent = Simulator::Schedule (tNext, &TutorialApp::SendPacket, this);
    }
}
