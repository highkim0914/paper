/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 INRIA
 *
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
 *
 * Author: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 */
#include "quic-stream-helper.h"
#include "ns3/quic-stream-server.h"
#include "ns3/quic-stream-client.h"
#include "ns3/uinteger.h"
#include "ns3/names.h"

namespace ns3 {

QuicStreamServerHelper::QuicStreamServerHelper (uint16_t port)
{
  m_factory.SetTypeId (QuicStreamServer::GetTypeId ());
  SetAttribute ("Port", UintegerValue (port));
}

void
QuicStreamServerHelper::SetAttribute (
  std::string name,
  const AttributeValue &value)
{
  m_factory.Set (name, value);
}

ApplicationContainer
QuicStreamServerHelper::Install (Ptr<Node> node) const
{
  return ApplicationContainer (InstallPriv (node));
}

ApplicationContainer
QuicStreamServerHelper::Install (std::string nodeName) const
{
  Ptr<Node> node = Names::Find<Node> (nodeName);
  return ApplicationContainer (InstallPriv (node));
}

ApplicationContainer
QuicStreamServerHelper::Install (NodeContainer c) const
{
  ApplicationContainer apps;
  for (NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i)
    {
      apps.Add (InstallPriv (*i));
    }

  return apps;
}

Ptr<Application>
QuicStreamServerHelper::InstallPriv (Ptr<Node> node) const
{
  Ptr<Application> app = m_factory.Create<QuicStreamServer> ();
  node->AddApplication (app);

  return app;
}

QuicStreamClientHelper::QuicStreamClientHelper (Address address, uint16_t port)
{
  m_factory.SetTypeId (QuicStreamClient::GetTypeId ());
  SetAttribute ("RemoteAddress", AddressValue (address));
  SetAttribute ("RemotePort", UintegerValue (port));
}

QuicStreamClientHelper::QuicStreamClientHelper (Ipv4Address address, uint16_t port)
{
  m_factory.SetTypeId (QuicStreamClient::GetTypeId ());
  SetAttribute ("RemoteAddress", AddressValue (Address(address)));
  SetAttribute ("RemotePort", UintegerValue (port));
}

QuicStreamClientHelper::QuicStreamClientHelper (Ipv6Address address, uint16_t port)
{
  m_factory.SetTypeId (QuicStreamClient::GetTypeId ());
  SetAttribute ("RemoteAddress", AddressValue (Address(address)));
  SetAttribute ("RemotePort", UintegerValue (port));
}

void
QuicStreamClientHelper::SetAttribute (std::string name, const AttributeValue &value)
{
  m_factory.Set (name, value);
}

ApplicationContainer
QuicStreamClientHelper::Install (std::vector <std::pair <Ptr<Node>, std::string> > clients) const
{
  ApplicationContainer apps;
  for (uint i = 0; i < clients.size (); i++)
    {
      apps.Add (InstallPriv (clients.at (i).first, clients.at (i).second, i));
    }

  return apps;
}

Ptr<Application>
QuicStreamClientHelper::InstallPriv (Ptr<Node> node, std::string algo, uint16_t clientId) const
{
  Ptr<Application> app = m_factory.Create<QuicStreamClient> ();
  app->GetObject<QuicStreamClient> ()->SetAttribute ("ClientId", UintegerValue (clientId));
  app->GetObject<QuicStreamClient> ()->Initialise (algo, clientId);
  node->AddApplication (app);
  return app;
}

} // namespace ns3
