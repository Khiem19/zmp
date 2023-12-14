#include "klient.hh"

int klient()
{
  Configuration Config;
  Reader reader;
  Set4LibInterfaces lib_handler;
  AbstractInterp4Command *command;
  std::istringstream stream;
  std::list<std::thread> threads;

  reader.init("config/commands.cmd");

  if (!reader.ReadFile("config/config.xml", Config))
  {
    return 1;
  }

  Scene scene(Config);
  Sender sender(&scene);
  if (!sender.OpenConnection())
    return 1;

  lib_handler.init(Config.libs);

  std::thread Thread4Sending(&Sender::Watching_and_Sending, &sender);

  std::string key;

  reader.execPreprocesor(stream);
  while (stream >> key) {
    command = lib_handler.execute(key);

    if (lib_handler.isParallel() && command != nullptr) {
        command->ReadParams(stream);
        threads.push_back(std::thread(&AbstractInterp4Command::ExecCmd, command, &scene));
    }
  }

  // Wait for thread completion if commands are not parallel
  if (!lib_handler.isParallel()) {
    for (auto &i : threads) {
        if (i.joinable()) {
            i.join();
        }
    }
    threads.clear();
  }

  sender.Send("Close\n");
  sender.CancelCountinueLooping();
  for (auto &i : threads)
  {
    if (i.joinable())
      i.join();
  }
  Thread4Sending.join();

  return 0;
}
