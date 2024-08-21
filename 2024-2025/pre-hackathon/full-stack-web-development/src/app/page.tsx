import { api, HydrateClient } from "~/trpc/server";

export default async function Home() {
  const hello = await api.hello({ text: "from tRPC" });

  return (
    <HydrateClient>
      <main>{hello.greeting}</main>
    </HydrateClient>
  );
}
