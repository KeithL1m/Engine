#pragma once

namespace KEIEngine
{
    namespace SaveUtil
    {
        void SaveVector3(const char* key, const KMath::Vector3& v, rapidjson::Document& doc, rapidjson::Value& member);
        void SaveQuaternion(const char* key, const KMath::Quaternion& q, rapidjson::Document& doc, rapidjson::Value& member);
        void SaveColor(const char* key, const Color& c, rapidjson::Document& doc, rapidjson::Value& member);
        void SaveFloat(const char* key, float value, rapidjson::Document& doc, rapidjson::Value& member);
        void SaveInt(const char* key, int value, rapidjson::Document& doc, rapidjson::Value& member);
        void SaveBool(const char* key, bool value, rapidjson::Document& doc, rapidjson::Value& member);
        void SaveString(const char* key, const char* value, rapidjson::Document& doc, rapidjson::Value& member);
        void SaveStringArray(const char* key, const std::vector<std::string>& values, rapidjson::Document& doc, rapidjson::Value& member);
    }
}
