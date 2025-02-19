////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Audio.hpp>

#include <iostream>
#include <string>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;


////////////////////////////////////////////////////////////
/// Play a sound
///
////////////////////////////////////////////////////////////
void playSound()
{
    // Load a sound buffer from a wav file
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("resources/killdeer.wav"))
        return;

    // Display sound information
    std::cout << "killdeer.wav:" << '\n'
              << " " << buffer.getDuration().asSeconds() << " seconds" << '\n'
              << " " << buffer.getSampleRate() << " samples / sec" << '\n'
              << " " << buffer.getChannelCount() << " channels" << std::endl;

    // Create a sound instance and play it
    sf::Sound sound(buffer);
    sound.play();

    // Loop while the sound is playing
    while (sound.getStatus() == sf::Sound::Playing)
    {
        // Leave some CPU time for other processes
        sf::sleep(sf::milliseconds(100));

        // Display the playing position
        std::cout << "\rPlaying... " << sound.getPlayingOffset().asSeconds() << " sec        ";
        std::cout << std::flush;
    }
    std::cout << std::endl << std::endl;
}


////////////////////////////////////////////////////////////
/// Play a music
///
////////////////////////////////////////////////////////////
// void playMusic(const fs::path& filename)
// {
//     // Load an ogg music file
//     sf::Music music;
//     if (!music.openFromFile("resources" / filename))
//         return;

//     // Display music information
//     std::cout << filename << ":" << '\n'
//               << " " << music.getDuration().asSeconds() << " seconds" << '\n'
//               << " " << music.getSampleRate() << " samples / sec" << '\n'
//               << " " << music.getChannelCount() << " channels" << std::endl;

//     // Play it
//     music.play();

//     // Loop while the music is playing
//     while (music.getStatus() == sf::Music::Playing)
//     {
//         // Leave some CPU time for other processes
//         sf::sleep(sf::milliseconds(100));

//         // Display the playing position
//         std::cout << "\rPlaying... " << music.getPlayingOffset().asSeconds() << " sec        ";
//         std::cout << std::flush;
//     }
//     std::cout << '\n' << std::endl;
// }


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
    // Play a sound
    playSound();

    // // Play music from an ogg file
    // playMusic("doodle_pop.ogg");

    // // Play music from a flac file
    // playMusic("ding.flac");

    // // Play music from a mp3 file
    // playMusic("ding.mp3");

    // Wait until the user presses 'enter' key
    std::cout << "Press enter to exit..." << std::endl;
    std::cin.ignore(10000, '\n');
}