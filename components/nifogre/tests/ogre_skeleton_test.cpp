/*
    Copyright (c) 2008-2013 the OpenMW developers.

    This file is part of OpenMW.

    OpenMW is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3,
    as published by the Free Software Foundation.

    You should have received a copy of the GNU General Public License
    along with OpenMW. If not, see <http://www.gnu.org/licenses/>.
*/

#include "ogre_common.cpp"

void C::doTest()
{
  SkeletonManager &skm = SkeletonManager::getSingleton();

  SkeletonPtr skp = skm.create("MySkel", "General");

  cout << "hello\n";
  /*
  MeshPtr msh = makeMesh("mesh1");

  // Display the mesh
  {
    SceneNode *node = mgr->getRootSceneNode()->createChildSceneNode("node");
    Entity *ent = mgr->createEntity("Mesh1", "mesh1");
    node->attachObject(ent);
    node->setPosition(0,0,4);
  }
  */
}
