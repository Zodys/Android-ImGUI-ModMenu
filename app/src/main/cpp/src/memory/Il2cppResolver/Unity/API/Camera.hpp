#pragma once

namespace Unity
{
    struct CameraFunctions_t
    {
        void* m_GetCurrent = nullptr;
        void* m_GetMain = nullptr;
        void* m_GetDepth = nullptr;
        void* m_SetDepth = nullptr;
        void* m_GetFieldOfView = nullptr;
        void* m_SetFieldOfView = nullptr;
        void* m_WorldToScreen = nullptr;
        void* m_WorldToCameraMatrix = nullptr;
        void* m_ProjectionMatrix = nullptr;
    };
    CameraFunctions_t m_CameraFunctions;

    class CCamera : public CGameObject
    {
    public:
        float GetDepth()
        {
            return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(m_CameraFunctions.m_GetDepth)(this);
        }

        void SetDepth(float m_fValue)
        {
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, float)>(m_CameraFunctions.m_SetDepth)(this, m_fValue);
        }

        float GetFieldOfView()
        {
            return reinterpret_cast<float(UNITY_CALLING_CONVENTION)(void*)>(m_CameraFunctions.m_GetFieldOfView)(this);
        }

        void SetFieldOfView(float m_fValue)
        {
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, float)>(m_CameraFunctions.m_SetFieldOfView)(this, m_fValue);
        }

        void WorldToScreen(Vector3& m_vWorld, Vector3& m_vScreen, int m_iEye = 2)
        {
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Vector3&, int, Vector3&)>(m_CameraFunctions.m_WorldToScreen)(this, m_vWorld, m_iEye, m_vScreen);
        }

        Matrix4x4 GetProjectionMatrix(){
            Matrix4x4 matrix;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Matrix4x4&)>(m_CameraFunctions.m_ProjectionMatrix)(this, matrix);
            return matrix;
        }

        Matrix4x4 GetWorldToCameraMatrix(){
            Matrix4x4 matrix;
            reinterpret_cast<void(UNITY_CALLING_CONVENTION)(void*, Matrix4x4&)>(m_CameraFunctions.m_WorldToCameraMatrix)(this, matrix);
            return matrix;
        }

        bool WorldToScreen(Vector3 &from, Vector2 &to, int ScreenCenterX, int ScreenCenterY)
        {

            Matrix4x4 V = GetWorldToCameraMatrix();
            Matrix4x4 P = GetProjectionMatrix();

            Matrix4x4 matrix = V * P;
            float ViewW = matrix._14 * from.x + matrix._24 * from.y + matrix._34 * from.z + matrix._44;

            if (ViewW > 0.00f)
            {
                ViewW = 1.0f / ViewW;

                to.x = ScreenCenterX + (matrix._11 * from.x + matrix._21 * from.y + matrix._31 * from.z + matrix._41) * ViewW * ScreenCenterX;
                to.y = ScreenCenterY - (matrix._12 * from.x + matrix._22 * from.y + matrix._32 * from.z + matrix._42) * ViewW * ScreenCenterY;
                return true;
            }
            return false;
        }
    };

    namespace Camera
    {
        void Initialize()
        {
            IL2CPP::SystemTypeCache::Initializer::Add(UNITY_CAMERA_CLASS);

            m_CameraFunctions.m_GetCurrent        = IL2CPP::ResolveCall(UNITY_CAMERA_GETCURRENT);
            m_CameraFunctions.m_GetMain            = IL2CPP::ResolveCall(UNITY_CAMERA_GETMAIN);
            m_CameraFunctions.m_GetDepth        = IL2CPP::ResolveCall(UNITY_CAMERA_GETDEPTH);
            m_CameraFunctions.m_SetDepth        = IL2CPP::ResolveCall(UNITY_CAMERA_SETDEPTH);
            m_CameraFunctions.m_GetFieldOfView    = IL2CPP::ResolveCall(UNITY_CAMERA_GETFIELDOFVIEW);
            m_CameraFunctions.m_SetFieldOfView    = IL2CPP::ResolveCall(UNITY_CAMERA_SETFIELDOFVIEW);
            m_CameraFunctions.m_WorldToScreen    = IL2CPP::ResolveCall(UNITY_CAMERA_WORLDTOSCREEN);
            m_CameraFunctions.m_ProjectionMatrix    = IL2CPP::ResolveCall(UNITY_CAMERA_GETPROJECTIONMATRIX);
            m_CameraFunctions.m_WorldToCameraMatrix    = IL2CPP::ResolveCall(UNITY_CAMERA_GETWORLDTOCAMERAMATRIX);
        }

        CCamera* GetCurrent()
        {
            return reinterpret_cast<CCamera*(UNITY_CALLING_CONVENTION)()>(m_CameraFunctions.m_GetCurrent)();
        }

        CCamera* GetMain()
        {
            return reinterpret_cast<CCamera*(UNITY_CALLING_CONVENTION)()>(m_CameraFunctions.m_GetMain)();
        }
    }

    enum m_eCameraType : int
    {
        m_eCameraType_Game = 1,
        m_eCameraType_SceneView = 2,
        m_eCameraType_Preview = 4,
        m_eCameraType_VR = 8,
        m_eCameraType_Reflection = 16,
    };

    enum m_eCameraEye : int
    {
        m_eCameraEye_Left = 0,
        m_eCameraEye_Right = 1,
        m_eCameraEye_Center = 2,
    };
}