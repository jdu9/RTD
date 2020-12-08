#include "Player.h"

void Player::update()
{
    if (mZoomIn) {
        mView.zoom(0.9f);
        mZoomIn = false;
    }

    else if (mZoomOut) {
        mView.zoom(1.1f);
        mZoomOut = false;
    }

    if (mUp) {
        mView.move(0,-15.f);
        mUp = false;
    }

    else if (mDown) {
        mView.move(0,15.f);
        mDown = false;
    }

    if (mLeft) {
        mView.move(-15.f,0);
        mLeft = false;
    }

    else if (mRight) {
        mView.move(15.f,0);
        mRight = false;
    }

    if (mView.getCenter().x < 0)
        mView.setCenter(0, mView.getCenter().y);
    else if (mView.getCenter().x > mMap.getWidth() * 50.f)
        mView.setCenter(mMap.getWidth() * 50.f, mView.getCenter().y);

    if (mView.getCenter().y < 0)
        mView.setCenter(mView.getCenter().x, 0);
    else if (mView.getCenter().y > mMap.getHeight() * 50.f)
        mView.setCenter(mView.getCenter().x, mMap.getHeight() * 50.f);
}
