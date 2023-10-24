#include "main.h"


bool IsObsoleteValue(HKEY hKey, const std::wstring& valueName) {
    return true;
}

void RecursivelyCheckRegistry(HKEY hKey, const std::wstring& keyPath) {
    HKEY subKey;
    if (RegOpenKeyEx(hKey, keyPath.c_str(), 0, KEY_READ, &subKey) == ERROR_SUCCESS) {
        // Перечислить все подключи в текущем ключе
        DWORD numSubKeys;
        if (RegQueryInfoKey(subKey, nullptr, nullptr, nullptr, &numSubKeys, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
            for (DWORD i = 0; i < numSubKeys; ++i) {
                std::vector<wchar_t> subkeyName(MAX_PATH);
                DWORD subkeyNameSize = MAX_PATH;
                if (RegEnumKeyEx(subKey, i, subkeyName.data(), &subkeyNameSize, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
                    // Рекурсивно проверить каждый подключ
                    RecursivelyCheckRegistry(subKey, subkeyName.data());
                }
            }
        }

        // Перечислить все значения в текущем ключе
        DWORD numValues;
        if (RegQueryInfoKey(subKey, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, &numValues, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
            for (DWORD j = 0; j < numValues; ++j) {
                std::vector<wchar_t> valueName(MAX_PATH);
                DWORD valueNameSize = MAX_PATH;
                if (RegEnumValue(subKey, j, valueName.data(), &valueNameSize, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
                    if (IsObsoleteValue(hKey, valueName.data())) {
                        std::wcout << L"Устаревшее значение: " << valueName.data() << std::endl;
                    }
                }
            }
        }

        RegCloseKey(subKey);
    }
}

int main() {
    RECT clientRect;
//    GetClientRect(hWnd, &clientRect);



    HKEY hKey;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        EnumerateRegistryKeys(hKey, L"HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft", NULL);
        RegCloseKey(hKey);
    }
}

void EnumerateRegistryKeys(HKEY hKey, const std::wstring& path, HWND hEdit) {

    DWORD dwBytesWritten;

    DWORD subKeys;
    DWORD maxSubKeyLen;
    DWORD values;
    DWORD maxValueNameLen;
    DWORD maxValueDataLen;

    if (RegQueryInfoKey(hKey, NULL, NULL, NULL, &subKeys, &maxSubKeyLen, NULL, &values, &maxValueNameLen, &maxValueDataLen, NULL, NULL) != ERROR_SUCCESS) {
        return;
    }

    if (values == 0 && subKeys == 0) {
        std::wcout << path << L"\r\n";
       // SendMessageW(hEdit, EM_SETSEL, -1, -1);
        //SendMessageW(hEdit, EM_REPLACESEL, 0, (LPARAM)(path + L"\r\n").c_str());

        return;
    }

    for (DWORD i = 0; i < subKeys; ++i) {
        WCHAR subKeyName[MAX_PATH];
        DWORD subKeyNameSize = sizeof(subKeyName);

        if (RegEnumKeyEx(hKey, i, subKeyName, &subKeyNameSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS) {
            HKEY subKey;
            if (RegOpenKeyEx(hKey, subKeyName, 0, KEY_READ, &subKey) == ERROR_SUCCESS) {
                EnumerateRegistryKeys(subKey, path + L"\\" + subKeyName, hEdit);
                RegCloseKey(subKey);
            }
        }
    }
}
