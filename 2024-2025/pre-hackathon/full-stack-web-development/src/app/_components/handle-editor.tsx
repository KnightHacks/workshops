"use client";

import { useState } from "react";
import { Button } from "~/components/ui/button";
import { Input } from "~/components/ui/input";
import { api } from "~/trpc/react";

export function HandleEditor({ handle }: { handle?: string }) {
  const [newHandle, setNewHandle] = useState(handle ?? "");
  const updateHandle = api.user.updateHandle.useMutation();

  return (
    <>
      <div>
        {handle && handle.length > 0
          ? `Your handle is`
          : "You don't a handle. Create one to interact with other users!"}
      </div>
      <form
        onSubmit={(e) => {
          e.preventDefault();
          updateHandle.mutate(newHandle);
        }}
      >
        <Input
          placeholder="Enter your new handle"
          value={newHandle}
          onChange={(e) => setNewHandle(e.target.value)}
        />
        <Button disabled={handle === newHandle} type="submit">
          Update Handle
        </Button>
      </form>
    </>
  );
}
