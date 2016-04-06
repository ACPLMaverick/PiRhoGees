﻿using UnityEngine;
using System.Collections;

public class CameraManager : Singleton<CameraManager>
{
    #region constants

    private const float CAMERA_ZOOM_MIN = 0.1f;
    private const float CAMERA_ZOOM_MAX = 10.0f;

    #endregion

    #region public

    public Camera CameraControlled;
    public float CameraMovementRate;
    public float CameraZoomRate;
    public GameObject Background0;

    #endregion

    #region private

    private Vector2 _bMin;
    private Vector2 _bMax;

    #endregion

    #region functions

    // Use this for initialization
    void Start ()
    {
        // acquire background min and max points

        SpriteRenderer sr = Background0.GetComponent<SpriteRenderer>();
        _bMin.x = sr.sprite.bounds.center.x - sr.sprite.bounds.extents.x;
        _bMin.y = sr.sprite.bounds.center.y - sr.sprite.bounds.extents.y;
        _bMax.x = sr.sprite.bounds.center.x + sr.sprite.bounds.extents.x;
        _bMax.y = sr.sprite.bounds.center.y + sr.sprite.bounds.extents.y;

        Transform tr = Background0.GetComponent<Transform>();
        Vector4 min4 = new Vector4(_bMin.x, _bMin.y, 0.0f, 1.0f);
        Vector4 max4 = new Vector4(_bMax.x, _bMax.y, 0.0f, 1.0f);
        min4 = tr.localToWorldMatrix * min4;
        max4 = tr.localToWorldMatrix * max4;

        _bMin = new Vector2(min4.x, min4.y);
        _bMax = new Vector2(max4.x, max4.y);

        Debug.Log(_bMin);
        Debug.Log(_bMax);

        // register for events

        InputManager.OnInputMove += MoveCamera;
        InputManager.OnInputZoom += ZoomCamera;
    }
	
	// Update is called once per frame
	void Update ()
    {
        
	}

    private void MoveCamera(Vector2 origin, Vector2 direction)
    {
        //Debug.Log(origin);
        //Debug.Log(direction);

        // check if we point the background or other object
        RaycastHit hit;

        Vector3 wp1 = CameraControlled.ScreenToWorldPoint(origin);
        Vector3 wp2 = CameraControlled.ScreenToWorldPoint(origin + direction);
        Vector3 deltaP = wp2 - wp1;

        Physics.Raycast(new Ray(wp1, new Vector3(0.0f, 0.0f, 1.0f)), out hit);
        
        // we hit other object or nothing - return
        if(hit.collider == null || hit.collider.gameObject != Background0)
        {
            return;
        }

        CameraControlled.transform.position += - deltaP * CameraMovementRate;

        FixCameraPositionBoundaries();
    }

    private void ZoomCamera(float amount)
    {
        float oldSize = CameraControlled.orthographicSize;
        CameraControlled.orthographicSize = Mathf.Clamp(CameraControlled.orthographicSize + amount * CameraZoomRate, CAMERA_ZOOM_MIN, CAMERA_ZOOM_MAX);

        FixCameraZoomBoundaries();
    }

    private void FixCameraPositionBoundaries()
    {
        // get point min and max for the camera view rectangle
        Vector3 cMinWorld = CameraControlled.ScreenToWorldPoint(new Vector3(0.0f, 0.0f, 0.0f));
        Vector3 cMaxWorld = CameraControlled.ScreenToWorldPoint(new Vector3(Screen.width, Screen.height, 0.0f));
        cMinWorld.z = 0.0f;
        cMaxWorld.z = 0.0f;
        Vector3 bMin3 = new Vector3(_bMin.x, _bMin.y, 0.0f);
        Vector3 bMax3 = new Vector3(_bMax.x, _bMax.y, 0.0f);

        cMinWorld = bMin3 - Vector3.Min(cMinWorld, new Vector3(_bMin.x, _bMin.y, 0.0f));
        cMaxWorld = -(Vector3.Max(cMaxWorld, new Vector3(_bMax.x, _bMax.y, 0.0f)) - bMax3);

        CameraControlled.transform.position += cMinWorld + cMaxWorld;
    }

    private void FixCameraZoomBoundaries()
    {
        uint trials = 100;
        float step = 0.01f;
        for(uint i = 0; i < trials; ++i)
        {
            // get point min and max for the camera view rectangle
            Vector3 cMinWorld = CameraControlled.ScreenToWorldPoint(new Vector3(0.0f, 0.0f, 0.0f));
            Vector3 cMaxWorld = CameraControlled.ScreenToWorldPoint(new Vector3(Screen.width, Screen.height, 0.0f));
            cMinWorld.z = 0.0f;
            cMaxWorld.z = 0.0f;
            Vector3 bMin3 = new Vector3(_bMin.x, _bMin.y, 0.0f);
            Vector3 bMax3 = new Vector3(_bMax.x, _bMax.y, 0.0f);

            cMinWorld = bMin3 - Vector3.Min(cMinWorld, new Vector3(_bMin.x, _bMin.y, 0.0f));
            cMaxWorld = -(Vector3.Max(cMaxWorld, new Vector3(_bMax.x, _bMax.y, 0.0f)) - bMax3);

            CameraControlled.transform.position += cMinWorld + cMaxWorld;

            if (cMinWorld.x == 0.0f && cMinWorld.y == 0.0f && cMaxWorld.x == 0.0f && cMaxWorld.y == 0.0f)
            {
                break;
            }
            else
            {
                CameraControlled.orthographicSize -= step;
            }
        }
        
    }

    #endregion
}
