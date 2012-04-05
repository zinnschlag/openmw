#include "BulletShapeLoader.h"



BulletShape::BulletShape(Ogre::ResourceManager* creator, const Ogre::String &name,
    Ogre::ResourceHandle handle, const Ogre::String &group, bool isManual,
    Ogre::ManualResourceLoader *loader) :
Ogre::Resource(creator, name, handle, group, isManual, loader)
{
    /* If you were storing a pointer to an object, then you would set that pointer to NULL here.
    */

    /* For consistency with StringInterface, but we don't add any parameters here
    That's because the Resource implementation of StringInterface is to
    list all the options that need to be set before loading, of which
    we have none as such. Full details can be set through scripts.
    */
    Shape = NULL;
    collide = true;
    createParamDictionary("BulletShape");
}

BulletShape::~BulletShape()
{
    deleteShape(Shape);
}

// farm out to BulletShapeLoader
void BulletShape::loadImpl()
{
    mLoader->loadResource(this);
}

void BulletShape::deleteShape(btCollisionShape* mShape)
{
    if(mShape!=NULL)
    {
        if(mShape->isCompound())
        {
            btCompoundShape* ms = static_cast<btCompoundShape*>(Shape);
            int a = ms->getNumChildShapes();
            for(int i=0; i <a;i++)
            {
                deleteShape(ms->getChildShape(i));
            }
        }
        delete mShape;
    }
    mShape = NULL;
}

void BulletShape::unloadImpl()
{
    deleteShape(Shape);
}

//TODO:change this?
size_t BulletShape::calculateSize() const
{
    return 1;
}



//=============================================================================================================
#if OGRE_VERSION_MAJOR == 1 && OGRE_VERSION_MINOR < 8
template<> BulletShapeManager *Ogre::Singleton<BulletShapeManager>::ms_Singleton = 0;
#else
template<> BulletShapeManager *Ogre::Singleton<BulletShapeManager>::msSingleton = 0;
#endif

BulletShapeManager *BulletShapeManager::getSingletonPtr()
{
#if OGRE_VERSION_MAJOR == 1 && OGRE_VERSION_MINOR < 8
    return ms_Singleton;
#else
    return msSingleton;
#endif
}

BulletShapeManager &BulletShapeManager::getSingleton()
{
#if OGRE_VERSION_MAJOR == 1 && OGRE_VERSION_MINOR < 8
    assert(ms_Singleton);
    return(*ms_Singleton);
#else
    assert(msSingleton);
    return(*msSingleton);
#endif
}

BulletShapeManager::BulletShapeManager()
{
    mResourceType = "BulletShape";

    // low, because it will likely reference other resources
    mLoadOrder = 30.0f;

    // this is how we register the ResourceManager with OGRE
    Ogre::ResourceGroupManager::getSingleton()._registerResourceManager(mResourceType, this);
}

BulletShapeManager::~BulletShapeManager()
{
    // and this is how we unregister it
    Ogre::ResourceGroupManager::getSingleton()._unregisterResourceManager(mResourceType);
}

BulletShapePtr BulletShapeManager::load(const Ogre::String &name, const Ogre::String &group)
{
    BulletShapePtr textf = getByName(name);

    if (textf.isNull())
        textf = create(name, group);

    textf->load();
    return textf;
}

Ogre::Resource *BulletShapeManager::createImpl(const Ogre::String &name, Ogre::ResourceHandle handle,
    const Ogre::String &group, bool isManual, Ogre::ManualResourceLoader *loader,
    const Ogre::NameValuePairList *createParams)
{
    BulletShape* res = new BulletShape(this, name, handle, group, isManual, loader);
    //if(isManual)
    //{
    //loader->loadResource(res);
    //}
    return res;
}


//====================================================================
void BulletShapeLoader::loadResource(Ogre::Resource *resource)
{}

void BulletShapeLoader::load(const std::string &name,const std::string &group)
{}
