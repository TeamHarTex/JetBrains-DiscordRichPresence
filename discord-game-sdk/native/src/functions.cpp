/*
 * JetBrains-DiscordRichPresence
 * Copyright (C) 2022  Team HarTex and contributors
 *
 * JetBrains-DiscordRichPresence is free software: you can redistribute
 * it and/or modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * JetBrains-DiscordRichPresence is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with JetBrains-DiscordRichPresence.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <cstring>
#include <jni.h>
#include <limits>
#include <string>

#include "functions.h"

template<int LENGTH>
void
CreateNativeString(JNIEnv& jniEnv, jbyteArray bytes, char target[LENGTH]) {
    std::fill_n(target, LENGTH, 0);

    jsize length = jniEnv.GetArrayLength(bytes);
    auto* buffer = (jbyte*) target;

    jniEnv.GetByteArrayRegion(bytes, 0, std::min(LENGTH - 1L, length), buffer);
}

std::string
CreateNativeString(JNIEnv& jniEnv, jbyteArray bytes) {
    jsize length = jniEnv.GetArrayLength(bytes);

    std::string target(length, ' ');
    target.reserve(length);

    jniEnv.GetByteArrayRegion(bytes, 0, length, (jbyte*) target.data());
    return target;
}

jbyteArray
CreateJavaString(JNIEnv& jniEnv, const char* string) {
    auto length = strlen(string);
    if (length > std::numeric_limits<jint>::max())
        return nullptr;

    jbyteArray bytes = jniEnv.NewByteArray((jint) length);
    jniEnv.SetByteArrayRegion(bytes, 0, (jint) length, (jbyte*) string);

    return bytes;
}
